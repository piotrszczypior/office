//
// Created by piotr on 4/17/24.
//

#ifndef OFFICE_STATE_HPP
#define OFFICE_STATE_HPP


#include "../model/Elevator.hpp"
#include "../model/Employee.hpp"
#include <vector>
#include <memory>

class State {
private:
    Elevator &elevator;
    std::vector<std::shared_ptr<Employee>> employees = std::vector<std::shared_ptr<Employee>>();
//    std::vector<Employee> employees = std::vector<Employee>();
public:

    explicit State(Elevator &elevator) : elevator(elevator) {};

    Elevator &get_elevator() {
        return elevator;
    }

    vector<std::shared_ptr<Employee>> get_employees() {
        return employees;
    }

//    vector<Employee> get_employees() {
//        return employees;
//    }

    void add_new_employee(const std::shared_ptr<Employee>& employee) {
        employees.push_back(employee);
    }

//    void add_new_employee(Employee &employee) {
//        employees.push_back(employee);
//    }

    void remove_employee(const std::shared_ptr<Employee>& employee) {
        for (int i = 0; i < employees.size(); ++i) {
            if (employees[i]->get_employee_name() == employee->get_employee_name() &&
                employees[i]->get_id() == employee->get_id()) {
                employees.erase(employees.begin() + i);
            }
        }
    }
};


#endif //OFFICE_STATE_HPP
