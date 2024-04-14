#ifndef OFFICE_EMPLOYEE_H
#define OFFICE_EMPLOYEE_H

#include <string>

using namespace std;

class Employee {
private:
    string employee_name;
    int color{};
    int position_x{}, position_y{};
    int speed;

public:
    explicit Employee() = default;

    explicit Employee(string employee_name, int color, int position_x, int position_y) :
            employee_name(employee_name), color(color), position_x(position_x), position_y(position_y) {};

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

    Employee &set_employee_name(string name) {
        this->employee_name = std::move(name);
        return *this;
    }

    Employee &set_speed(int s) {
        this->speed = s;
        return *this;
    }

//    Employee &set_in_elevator(bool is_in_elevator) {
//        this->in_elevator = is_in_elevator;
//        return *this;
//    }

    string get_employee_name() const {
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

//    bool is_in_elevator() {
//        return in_elevator;
//    }
};

#endif //OFFICE_EMPLOYEE_H
