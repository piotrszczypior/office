#ifndef OFFICE_ELEVATORANIMATION_HPP
#define OFFICE_ELEVATORANIMATION_HPP

#include "model/Elevator.hpp"
#include "config/config.hpp"
#include <iostream>
#include <thread>

class ElevatorAnimation {
private:
    WINDOW *shaft{};

public:
    explicit ElevatorAnimation(WINDOW *s) : shaft(s) {}

    void redraw(Elevator &elevator) {
        const std::string inside_message = "Inside: " + to_string(elevator.get_employees().size());


//        for (const auto& employee : elevator.get_employees()) {
//            inside_message += employee.get_employee_name() + " ";
//        }
        std::lock_guard<std::mutex> writing_lock(mx_drawing);

        werase(shaft);
        box(shaft, 0, 0);

        for (int y = elevator.get_position_y(); y < elevator.get_position_y() + ELEVATOR_HEIGHT; ++y) {
            mvwhline(shaft, y, elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_WIDTH);
        }

        if (elevator.get_position_y() >= FIRST_FLOOR) {
            for (int y = 1; y < 1 + ELEVATOR_HEIGHT; ++y) {
                mvwhline(shaft, y, elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_WIDTH);
            }
        }

        int message_start_x = elevator.get_position_x() + (ELEVATOR_WIDTH - inside_message.length()) / 2;
        int message_y = elevator.get_position_y() + ELEVATOR_HEIGHT / 2;
        mvwprintw(shaft, message_y, message_start_x, "%s", inside_message.c_str());

        wrefresh(shaft);
    }
};


#endif //OFFICE_ELEVATORANIMATION_HPP
