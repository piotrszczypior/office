//
// Created by piotr on 4/13/24.
//

#ifndef OFFICE_SIMULATION_HPP
#define OFFICE_SIMULATION_HPP

#include <vector>
#include <thread>
#include "config/config.hpp"
#include "model/Elevator.hpp"
#include "ElevatorAnimation.hpp"

using namespace std;

class Simulation {
    std::vector<std::thread> employees_threads;
    std::thread elevator_thread;
    ElevatorAnimation elevatorAnimation;
    Elevator elevator;

    void create_employee_threads();

    void create_elevator_thread();

    void elevator_work();

    void person_work();

public:
    explicit Simulation(ElevatorAnimation &elevatorAnimation, Elevator &elevator)
            : elevatorAnimation(elevatorAnimation), elevator(elevator) {};

    void run();
};

void Simulation::run() {
    create_employee_threads();
    elevator_thread.join();
}


void Simulation::create_elevator_thread() {

}

void Simulation::create_employee_threads() {
    elevator_thread = std::thread([this]() -> void {
        elevator_work();
    });
}

void Simulation::elevator_work() {

    while (program_running.load()) {
        elevatorAnimation.draw(elevator);

        elevator.set_position_y(elevator.get_position_y() + 1);

        if (FLOOR_POSITIONS[elevator.get_current_floor() - 1] == elevator.get_position_y()) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            elevator.set_current_floor(elevator.get_current_floor() - 1);
        }

        if (elevator.get_position_y() >= 37) {
            elevator.set_position_y(1);
            elevator.set_current_floor(3);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

#endif //OFFICE_SIMULATION_HPP
