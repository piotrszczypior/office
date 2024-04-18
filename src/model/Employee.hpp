#ifndef OFFICE_EMPLOYEE_HPP
#define OFFICE_EMPLOYEE_HPP

#include <string>
#include <utility>
#include "ncurses.h"

using namespace std;

class Employee {
private:
    int id;
    char employee_name;
    int color{};
    int position_x{}, position_y{};
    int speed{};
    bool inside_elevator = false;

public:
    explicit Employee() = default;

    Employee &set_id(int id) {
        this->id = id;
        return *this;
    }

    Employee &set_position_x(int x) {
        this->position_x = x;
        return *this;
    }

    Employee &set_position_y(int y) {
        this->position_y = y;
        return *this;
    }

    Employee &set_color(int c) {
        this->color = c;
        return *this;
    }

    Employee &set_employee_name(char name) {
        this->employee_name = name;
        return *this;
    }

    Employee &set_speed(int s) {
        this->speed = s;
        return *this;
    }

    Employee &set_inside_elevator(bool inside) {
        this->inside_elevator = inside;
        return *this;
    }

    int get_id() const {
        return id;
    }

    char get_employee_name() const {
        return employee_name;
    }

    int get_color() const {
        return color;
    }

    int get_position_x() const {
        return position_x;
    }

    int get_position_y() const {
        return position_y;
    }

    int get_speed() const {
        return speed;
    }

    bool is_inside_elevator() {
        return inside_elevator;
    }
};

#endif //OFFICE_EMPLOYEE_HPP
