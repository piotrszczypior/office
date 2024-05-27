#ifndef OFFICE_ELEVATOR_HPP
#define OFFICE_ELEVATOR_HPP

#include "Employee.hpp"
#include <vector>
#include <memory>

using namespace std;

class Employee;

class Elevator {
private:
    int position_x{};
    int position_y{};
    std::vector<std::shared_ptr<Employee>> employees_inside = std::vector<std::shared_ptr<Employee>>();

    int current_floor = 0;
    int destination_floor = 0;

public:

    explicit Elevator() = default;

    explicit Elevator(int x, int y) : position_x(x), position_y(y) {}

    Elevator &set_position_x(int x) {
        this->position_x = x;
        return *this;
    }

    Elevator &set_position_y(int y) {
        this->position_y = y;
        return *this;
    }

    Elevator &set_current_floor(int floor) {
        this->current_floor = floor;
        return *this;
    }

    Elevator &set_destination(int floor) {
        this->destination_floor = floor;
        return *this;
    }

    int get_position_x() const {
        return position_x;
    }

    int get_position_y() const {
        return position_y;
    }

    int get_current_floor() const {
        return current_floor;
    }

    int get_destination_floor() const {
        return destination_floor;
    }
};


#endif //OFFICE_ELEVATOR_HPP
