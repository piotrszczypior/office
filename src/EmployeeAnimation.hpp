//
// Created by piotr on 4/13/24.
//

#ifndef OFFICE_EMPLOYEEANIMATION_HPP
#define OFFICE_EMPLOYEEANIMATION_HPP

#include <ncurses.h>
#include "model/Employee.hpp"
#include "config/config.hpp"

class EmployeeAnimation {
    WINDOW *office_exit;

    WINDOW *print_third_floor_exit() {
        const int start_y = 3;
        const int start_x = 60;

        WINDOW *third_floor_exit = newwin(EMPLOYEE_EXIT_HEIGHT, EMPLOYEE_EXIT_WIDTH, start_y, start_x);

        redraw_box(third_floor_exit);

        wrefresh(third_floor_exit);
        return third_floor_exit;
    }

    static void redraw_box(WINDOW *window) {
        for (int x = 0; x < EMPLOYEE_EXIT_WIDTH; ++x) {
            mvwaddch(window, 0, x, ACS_HLINE);
        }

        for (int y = 0; y < EMPLOYEE_EXIT_HEIGHT; ++y) {
            mvwaddch(window, y, 0, ACS_VLINE);
        }

        for (int x = 0; x < EMPLOYEE_EXIT_WIDTH; ++x) {
            mvwaddch(window, EMPLOYEE_EXIT_HEIGHT - 1, x, ACS_HLINE);
        }

        mvwaddch(window, 0, 0, ACS_ULCORNER);
        mvwaddch(window, EMPLOYEE_EXIT_HEIGHT - 1, 0, ACS_LLCORNER);
        mvwaddch(window, 0, EMPLOYEE_EXIT_WIDTH - 1, ACS_URCORNER);
        mvwaddch(window, EMPLOYEE_EXIT_HEIGHT - 1, EMPLOYEE_EXIT_WIDTH - 1, ACS_LRCORNER);
    }

public:

    void redraw(Employee employee) {
        werase(office_exit);
        redraw_box(office_exit);

//        int x = std::max(1, std::min(employee.get_position_x(), EMPLOYEE_EXIT_WIDTH - 2));

        mvwprintw(office_exit, employee.get_position_y(), employee.get_position_x(), "%s", employee.get_employee_name().c_str());

        wrefresh(office_exit);
    }

    EmployeeAnimation() {
        office_exit = print_third_floor_exit();
    }
};


#endif //OFFICE_EMPLOYEEANIMATION_HPP
