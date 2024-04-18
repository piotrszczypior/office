#ifndef OFFICE_SIMULATIONSERVICE_HPP
#define OFFICE_SIMULATIONSERVICE_HPP

#include <vector>
#include <thread>
#include <random>
#include <map>

#include "../config/config.hpp"
#include "../model/Elevator.hpp"
#include "../builder/EmployeeBuilder.hpp"
#include "State.hpp"
#include <iostream>

using namespace std;

class SimulationService {
    std::vector<std::thread> employees_threads = vector<std::thread>();
    std::thread elevator_thread;
    std::thread drawing_thread;
    vector<Employee> employees = vector<Employee>();

    State &state;

    void create_employee_threads();

    void create_elevator_thread();

    void elevator_work();

    void employee_work(const std::shared_ptr<Employee> &employee);

public:
    explicit SimulationService(State &state) : state(state) {};

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
    for (int i = 0; program_running; ++i) {
        Employee employee = EmployeeBuilder::build().set_id(i);

        std::shared_ptr<Employee> employee_ptr = std::make_shared<Employee>(employee);
        state.add_new_employee(employee_ptr);

        employees_threads.emplace_back([this, employee_ptr]() -> void {
            employee_work(employee_ptr);
        });
        this_thread::sleep_for(chrono::seconds(rand() % 4));
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

    state.get_elevator().set_destination(floor_distribution(gen));

    while (program_running) {
        state.get_elevator().set_position_y(state.get_elevator().get_position_y() + 1);

        if (FLOOR_POSITIONS[state.get_elevator().get_current_floor() - 1] == state.get_elevator().get_position_y()) {
            state.get_elevator().set_current_floor(state.get_elevator().get_current_floor() - 1);
        }

        if (FLOOR_POSITIONS[state.get_elevator().get_destination_floor()] + 2 ==
            state.get_elevator().get_position_y()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            state.get_elevator().remove_all_passengers();
        }

        if (state.get_elevator().get_position_y() >= SHAFT_HEIGHT) {
            state.get_elevator().set_position_y(ELEVATOR_START_Y);
            state.get_elevator().set_current_floor(3);
            state.get_elevator().set_destination(floor_distribution(gen));
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void SimulationService::employee_work(const std::shared_ptr<Employee> &employee) {
    std::uniform_int_distribution<> position_y_distribution{-1, 1};
    std::random_device random_device;

    while (program_running) {
        this_thread::sleep_for(chrono::milliseconds(200 * employee->get_speed()));
        if (employee->get_position_x() < TUNNEL_WIDTH + ENTRY_TUNNEL_X - 1) {

            employee->set_position_x(employee->get_position_x() + 1);

            continue;
        }

        while (program_running) {
            this_thread::sleep_for(chrono::milliseconds(50));

            if (state.get_elevator().get_current_floor() == 3) {
                employee->set_inside_elevator(true);
                state.get_elevator().add_passenger(employee);
                break;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));

        while (program_running &&
               state.get_elevator().get_current_floor() != state.get_elevator().get_destination_floor()) {
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        employee->set_inside_elevator(false);
        employee->set_position_y(
                FLOOR_POSITIONS[state.get_elevator().get_destination_floor()] + employee->get_position_y() - 2);
        employee->set_position_x(EXIT_TUNNEL_X);
        this_thread::sleep_for(chrono::milliseconds(500 * employee->get_speed()));

        while (program_running) {
            this_thread::sleep_for(chrono::milliseconds(200 * employee->get_speed()));

            employee->set_position_x(employee->get_position_x() + 1);

            if (employee->get_position_x() >= TUNNEL_WIDTH + EXIT_TUNNEL_X) {
                state.remove_employee(employee);
                return;
            }
        }
    }
}

#endif //OFFICE_SIMULATIONSERVICE_HPP
