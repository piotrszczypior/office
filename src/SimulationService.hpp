#ifndef OFFICE_SIMULATIONSERVICE_HPP
#define OFFICE_SIMULATIONSERVICE_HPP

#include <vector>
#include <thread>
#include <random>
#include <map>

#include "config/config.hpp"
#include "model/Elevator.hpp"
#include "ElevatorAnimation.hpp"
#include "EmployeeAnimation.hpp"
#include "builder/EmployeeBuilder.hpp"

using namespace std;

class SimulationService {
    std::vector<std::thread> employees_threads = vector<std::thread>();
    std::thread elevator_thread;
    std::thread drawing_thread;
    vector<Employee> employees = vector<Employee>();

    std::map<std::string, bool> occupiedPositions;

    Elevator &elevator;
    ElevatorAnimation elevatorAnimation;

    void create_employee_threads();

    void create_elevator_thread();

    void elevator_work();

    void employee_work(Employee &employee);

    string makeKey(int x, int y);

    bool isPositionFree(int x, int y);

    void occupyPosition(int x, int y);

    void freePosition(int x, int y);

public:
    explicit SimulationService(ElevatorAnimation &elevatorAnimation, Elevator &elevator)
            : elevatorAnimation(elevatorAnimation), elevator(elevator) {};

    void run();
};

void SimulationService::run() {
    create_elevator_thread();
    create_employee_threads();

    for (auto &employee_thread: employees_threads) {
        employee_thread.join();
    }
    elevator_thread.join();
}


void SimulationService::create_employee_threads() {
    EmployeeBuilder employeeBuilder = EmployeeBuilder();
    for (int i = 0; i < EMPLOYEE_NUMBER; ++i) {
        employees.emplace_back(employeeBuilder.build());
    }

    for (int i = 0; i < EMPLOYEE_NUMBER; ++i) {
        employees_threads.emplace_back([this, i]() -> void {
            employee_work(employees[i]);
        });
    }
}

void SimulationService::create_elevator_thread() {
    elevator_thread = std::thread([this]() -> void {
        elevator_work();
    });
}

void SimulationService::elevator_work() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> floor_distribution(0, 2);

    elevator.set_destination(floor_distribution(gen));

    while (program_running.load()) {
        elevatorAnimation.redraw(elevator);

        elevator.set_position_y(elevator.get_position_y() + 1);

        if (FLOOR_POSITIONS[elevator.get_current_floor() - 1] == elevator.get_position_y()) {
            elevator.set_current_floor(elevator.get_current_floor() - 1);
        }

        if (FLOOR_POSITIONS[elevator.get_destination_floor()] == elevator.get_position_y()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            elevator.remove_all_passengers();
        }

        if (elevator.get_position_y() >= (SHAFT_HEIGHT - ELEVATOR_HEIGHT)) {
            elevator.set_position_y(1);
            elevator.set_current_floor(3);
            elevator.set_destination(floor_distribution(gen));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void SimulationService::employee_work(Employee &employee) {
    WINDOW *employee_window = newwin(1, 2, employee.get_position_y(), employee.get_position_x());
    wattron(employee_window, COLOR_PAIR(employee.get_color()));
    std::uniform_int_distribution<> position_y_distribution{-1, 1};
    std::random_device random_device;
    std::mt19937 generator{random_device()};

    occupyPosition(employee.get_position_x(), employee.get_position_y());

    while (program_running.load()) {
        this_thread::sleep_for(chrono::milliseconds(300 * employee.get_speed()));

        if (employee.get_position_x() < TUNNEL_WIDTH + ENTRY_TUNNEL_X - 1) {
            if (isPositionFree(employee.get_position_x() + 1, employee.get_position_y())) {

                freePosition(employee.get_position_x(), employee.get_position_y());
                employee.set_position_x(employee.get_position_x() + 1);
                occupyPosition(employee.get_position_x(), employee.get_position_y());

                std::lock_guard<std::mutex> guard(mx_drawing);
                werase(employee_window);
                mvwin(employee_window, employee.get_position_y(), employee.get_position_x());
                mvwprintw(employee_window, 0, 1, "%s", employee.get_employee_name().c_str());
                wrefresh(employee_window);

            }
            continue;
        }

        freePosition(employee.get_position_x(), employee.get_position_y());
        while (program_running.load()) {
            this_thread::sleep_for(chrono::milliseconds(50));

            if (elevator.get_current_floor() == 3) {
                elevator.add_passenger(employee);
                break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));

        while (program_running.load() && elevator.get_current_floor() != elevator.get_destination_floor()) {
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        employee.set_position_y(
                FLOOR_POSITIONS[elevator.get_destination_floor()] + employee.get_position_y() - 2);
        employee.set_position_x(EXIT_TUNNEL_X);
        this_thread::sleep_for(chrono::milliseconds(500 * employee.get_speed()));

        while (program_running.load()) {
            this_thread::sleep_for(chrono::milliseconds(300 * employee.get_speed()));

            freePosition(employee.get_position_x(), employee.get_position_y());
            employee.set_position_x(employee.get_position_x() + 1);
            occupyPosition(employee.get_position_x(), employee.get_position_y());

            std::lock_guard<std::mutex> guard(mx_drawing);
            werase(employee_window);
            mvwin(employee_window, employee.get_position_y(), employee.get_position_x());
            mvwprintw(employee_window, 0, 1, "%s", employee.get_employee_name().c_str());
            wrefresh(employee_window);

            if (employee.get_position_x() >= TUNNEL_WIDTH + EXIT_TUNNEL_X) {
                freePosition(employee.get_position_x(), employee.get_position_y());
                employee.set_position_x(ENTRY_TUNNEL_X + 1);
                employee.set_position_y(ENTRY_TUNNEL_Y + TUNNEL_HEIGHT / 2 + position_y_distribution(generator));
                werase(employee_window);
                wrefresh(employee_window);

                break;
            }
        }
    }
}

std::string SimulationService::makeKey(int x, int y) {
    return std::to_string(x) + "," + std::to_string(y);
}

bool SimulationService::isPositionFree(int x, int y) {
    std::lock_guard<std::mutex> lock(mx_positions);
    auto key = makeKey(x, y);
    return occupiedPositions.find(key) == occupiedPositions.end();
}

void SimulationService::occupyPosition(int x, int y) {
    std::lock_guard<std::mutex> lock(mx_positions);
    occupiedPositions[makeKey(x, y)] = true;
}

void SimulationService::freePosition(int x, int y) {
    std::lock_guard<std::mutex> lock(mx_positions);
    occupiedPositions.erase(makeKey(x, y));
}


#endif //OFFICE_SIMULATIONSERVICE_HPP
