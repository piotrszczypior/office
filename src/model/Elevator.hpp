#ifndef OFFICE_ELEVATOR_H
#define OFFICE_ELEVATOR_H

using namespace std;

class Elevator {
private:
    int position_x{};
    int position_y{};
    vector<Employee> employees_inside = vector<Employee>();

    int current_floor = 0;

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

    int get_position_x() const {
        return position_x;
    }

    int get_position_y() const {
        return position_y;
    }

    int get_current_floor() const {
        return current_floor;
    }

    vector<Employee> get_employees() {
        return employees_inside;
    }

    bool add_passenger(Employee &employee) {
        if (current_floor != 3) {
            return false;
        }
        employees_inside.push_back(employee);
        return true;
    }

    void remove_all_passengers() {
        employees_inside.clear();
    }
};


#endif //OFFICE_ELEVATOR_H
