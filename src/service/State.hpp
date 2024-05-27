//
// Created by piotr on 4/17/24.
//

#ifndef OFFICE_STATE_HPP
#define OFFICE_STATE_HPP


#include "../model/Elevator.hpp"
#include "../model/Employee.hpp"

#include "../config/config.hpp"
#include <vector>
#include <memory>
#include <condition_variable>
#include <algorithm>

class State {
private:
    Elevator &elevator;
    std::mutex employees_mutex;
    std::vector<std::shared_ptr<Employee>> employees = std::vector<std::shared_ptr<Employee>>();
    int EXITED_EMPLOYEES[3] = {0, 0, 0};

public:
    int employees_in_elevator = 0;

    explicit State(Elevator &elevator) : elevator(elevator) {};

    Elevator &get_elevator() {
        return elevator;
    }

    bool can_employee_enter_elevator() {
        return elevator.get_current_floor() == 3 && employees_in_elevator <= MAX_EMPLOYEE_IN_ELEVATOR;
    }

    bool has_elevator_arrived_on_destination() {
        return elevator.get_current_floor() == elevator.get_destination_floor();
    }

    vector<std::shared_ptr<Employee>> get_employees() {
        return employees;
    }

    void add_new_employee(const std::shared_ptr<Employee> &employee) {
        employees.push_back(employee);
    }

    void record_exiting(int destination) {
        EXITED_EMPLOYEES[destination]++;
    }

    int* get_record() {
        return EXITED_EMPLOYEES;
    }

    void remove_employee(const std::shared_ptr<Employee> &employee) {
        std::lock_guard<std::mutex> lock(employees_mutex);
        auto it = std::find_if(employees.begin(), employees.end(), [&](const std::shared_ptr<Employee> &e) {
            return e->get_id() == employee->get_id() && e->get_employee_name() == employee->get_employee_name();
        });

        if (it != employees.end()) {
            employees.erase(it);
        }
    }
};


#endif //OFFICE_STATE_HPP
