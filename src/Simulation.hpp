#ifndef OFFICE_SIMULATION_HPP
#define OFFICE_SIMULATION_HPP

#include <vector>
#include <thread>
#include "config/config.hpp"
#include "model/Elevator.hpp"
#include "ElevatorAnimation.hpp"
#include "EmployeeAnimation.hpp"

using namespace std;

class Simulation {
    std::vector<std::thread> employees_threads = vector<std::thread>();
    std::thread elevator_thread;
    ElevatorAnimation elevatorAnimation;
    Elevator elevator;
    EmployeeAnimation employeeAnimation = EmployeeAnimation();

    void create_employee_threads();

    void create_elevator_thread();

    void elevator_work();

    void employee_work(Employee employee);

public:
    explicit Simulation(ElevatorAnimation &elevatorAnimation, Elevator &elevator)
            : elevatorAnimation(elevatorAnimation), elevator(elevator) {};

    void run();

    Employee create_employee();
};

void Simulation::run() {
    create_elevator_thread();
    create_employee_threads();

    for (auto &employee_thread : employees_threads) {
        employee_thread.join();
    }
    elevator_thread.join();
}


void Simulation::create_employee_threads() {
    vector<Employee> employees = vector<Employee>();
    for (int i = 0; i < EMPLOYEE_NUMBER; ++i) {
        employees.emplace_back(create_employee());
    }

    for (int i = 0; i < EMPLOYEE_NUMBER; ++i) {
        employees_threads.emplace_back([this, i, employees]() -> void {
            this->employee_work(employees[i]);
        });
    }
}

void Simulation::create_elevator_thread() {
    elevator_thread = std::thread([this]() -> void {
        elevator_work();
    });
}

void Simulation::elevator_work() {

    while (program_running.load()) {
        elevatorAnimation.redraw(elevator);

        elevator.set_position_y(elevator.get_position_y() + 1);

        if (FLOOR_POSITIONS[elevator.get_current_floor() - 1] == elevator.get_position_y()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            elevator.set_current_floor(elevator.get_current_floor() - 1);
        }

        if (elevator.get_position_y() >= (SHAFT_HEIGHT - ELEVATOR_HEIGHT)) {
            elevator.set_position_y(1);
            elevator.set_current_floor(3);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Simulation::employee_work(Employee employee) {
    while (program_running.load()) {
        this_thread::sleep_for(chrono::milliseconds(150 * employee.get_speed()));
        employeeAnimation.redraw(employee);

        if(employee.get_position_x() < EMPLOYEE_EXIT_WIDTH) {
            employee.set_position_x(employee.get_position_x() + 1);
        } else {
            employee.set_position_x(EMPLOYEE_START_X);
        }

    }
}

Employee Simulation::create_employee() {
    return Employee()
            .set_position_x(EMPLOYEE_START_X)
            .set_position_y(EMPLOYEE_START_Y)
            .set_employee_name("P")
            .set_color(1)
            .set_speed(2);
}

#endif //OFFICE_SIMULATION_HPP
