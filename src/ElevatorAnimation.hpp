#ifndef OFFICE_ELEVATORANIMATION_HPP
#define OFFICE_ELEVATORANIMATION_HPP

#include "model/Elevator.hpp"
#include "config/config.hpp"
#include <iostream>
#include <thread>

class ElevatorAnimation {
private:
    WINDOW *shaft{};

    void generate_shaft() {
        const int start_y = 3;
        const int start_x = (COLS - SHAFT_WIDTH) / 2;

        shaft = newwin(SHAFT_HEIGHT, SHAFT_WIDTH, start_y, start_x);

        box(shaft, 0, 0);
        wrefresh(shaft);
    }

public:
    explicit ElevatorAnimation() {
        generate_shaft();
    }

    void redraw(Elevator &elevator) {
        std::string inside_message;


        for (const auto& employee : elevator.get_employees()) {
            inside_message += employee.get_employee_name() + " ";
        }

        if (inside_message.empty()) {
            inside_message = "Elevator empty";
        }

        std::lock_guard<std::mutex> writing_lock(mx_drawing);

        werase(shaft);
        box(shaft, 0, 0);

        for (int y = elevator.get_position_y(); y < elevator.get_position_y() + ELEVATOR_HEIGHT; ++y) {
            mvwvline(shaft, elevator.get_position_y(), elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_HEIGHT);
            mvwvline(shaft, elevator.get_position_y(), elevator.get_position_x() + ELEVATOR_WIDTH - 1, ' ' | A_REVERSE, ELEVATOR_HEIGHT);

            mvwhline(shaft, elevator.get_position_y(), elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_WIDTH);
            mvwhline(shaft, elevator.get_position_y() + ELEVATOR_HEIGHT - 1, elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_WIDTH);
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
