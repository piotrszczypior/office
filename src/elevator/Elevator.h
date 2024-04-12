//
// Created by piotr on 4/6/24.
//

#ifndef OFFICE_ELEVATOR_H
#define OFFICE_ELEVATOR_H

#include <ncurses.h>

using namespace std;

class Elevator {
private:
    int current_floor = -1;

    WINDOW *elevator_window{};

public:

    void draw_elevator();

    void draw_elevator_shaft();

};


#endif //OFFICE_ELEVATOR_H
