#ifndef OFFICE_ELEVATOR_H
#define OFFICE_ELEVATOR_H

using namespace std;

class Elevator {
private:
    int position_x{};
    int position_y{};

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
};


#endif //OFFICE_ELEVATOR_H
