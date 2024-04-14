#ifndef OFFICE_SIMULATION_HPP
#define OFFICE_SIMULATION_HPP

#include <vector>
#include <thread>
#include <random>

#include "config/config.hpp"
#include "model/Elevator.hpp"
#include "ElevatorAnimation.hpp"
#include "EmployeeAnimation.hpp"

using namespace std;

class Simulation {
    std::vector<std::thread> employees_threads = vector<std::thread>();
    std::thread elevator_thread;
    std::thread drawing_thread;

    vector<Employee> employees = vector<Employee>();

    ElevatorAnimation elevatorAnimation;
    Elevator elevator;
    EmployeeAnimation employeeAnimation = EmployeeAnimation();

    void create_employee_threads();

    void create_elevator_thread();

    void elevator_work();

    void employee_work(Employee &employee);

public:
    explicit Simulation(ElevatorAnimation &elevatorAnimation, Elevator &elevator)
            : elevatorAnimation(elevatorAnimation), elevator(elevator) {};

    void run();

    static Employee create_employee();

    void create_drawing_thread();
};

void Simulation::run() {
    create_elevator_thread();
    create_employee_threads();
    create_drawing_thread();

    for (auto &employee_thread : employees_threads) {
        employee_thread.join();
    }
    elevator_thread.join();
    drawing_thread.join();
}


void Simulation::create_employee_threads() {
    for (int i = 0; i < EMPLOYEE_NUMBER; ++i) {
        employees.emplace_back(create_employee());
    }

    for (int i = 0; i < EMPLOYEE_NUMBER; ++i) {
        employees_threads.emplace_back([this, i]() -> void {
            employee_work(employees[i]);
        });
    }
}

void Simulation::create_elevator_thread() {
    elevator_thread = std::thread([this]() -> void {
        elevator_work();
    });
}

void Simulation::elevator_work() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> floor_distribution(0, 2);

//    WINDOW *employee_window = newwin(EMPLOYEE_)

    int floor = floor_distribution(gen);

    while (program_running.load()) {
        elevatorAnimation.redraw(elevator);

        elevator.set_position_y(elevator.get_position_y() + 1);

        if (FLOOR_POSITIONS[elevator.get_current_floor() - 1] == elevator.get_position_y()) {
            elevator.set_current_floor(elevator.get_current_floor() - 1);
        }

        if (FLOOR_POSITIONS[floor] == elevator.get_position_y()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            elevator.remove_all_passengers();
        }

        if (elevator.get_position_y() >= (SHAFT_HEIGHT - ELEVATOR_HEIGHT)) {
            elevator.set_position_y(1);
            elevator.set_current_floor(3);
            floor = floor_distribution(gen);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Simulation::employee_work(Employee &employee) {
    while (program_running.load()) {
        this_thread::sleep_for(chrono::milliseconds(300 * employee.get_speed()));

        if(employee.get_position_x() < EMPLOYEE_EXIT_WIDTH) {
            employee.set_position_x(employee.get_position_x() + 1);
            continue;
        }

        while (!employee.is_in_elevator() && program_running.load()) {
            employee.set_in_elevator(elevator.add_passenger(employee));
        }
    }
}

Employee Simulation::create_employee() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> speed_dist(1, 5);

    std::uniform_int_distribution<> name_dist('A', 'Z');

    char random_char = static_cast<char>(name_dist(gen));
    std::string random_name = std::string(1, random_char);

    int random_speed = speed_dist(gen);

    return Employee()
            .set_position_x(EMPLOYEE_START_X)
            .set_position_y(EMPLOYEE_START_Y)
            .set_employee_name(random_name)
            .set_color(1)
            .set_speed(random_speed)
            .set_in_elevator(false);
}

void Simulation::create_drawing_thread() {
    drawing_thread = std::thread([this]() -> void {
        while (program_running.load()) {
            employeeAnimation.redraw(employees);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });
}

#endif //OFFICE_SIMULATION_HPP
