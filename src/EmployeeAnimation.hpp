//
// Created by piotr on 4/13/24.
//

#ifndef OFFICE_EMPLOYEEANIMATION_HPP
#define OFFICE_EMPLOYEEANIMATION_HPP

#include <ncurses.h>
#include "model/Employee.hpp"
#include "config/config.hpp"

class EmployeeAnimation {
public:
    static WINDOW *print_floor_tunnel(int position_x, int position_y) {
        WINDOW *floor_tunnel = newwin(TUNNEL_HEIGHT, TUNNEL_WIDTH, position_y, position_x);

        draw_box(floor_tunnel);

        wrefresh(floor_tunnel);
        return floor_tunnel;
    }

private:
    static void draw_box(WINDOW *window) {
//        mvwaddch(window, 0, 0, ACS_ULCORNER);
        for (int x = 1; x < TUNNEL_WIDTH - 1; ++x) {
            mvwaddch(window, 0, x, ACS_HLINE);
        }
//        mvwaddch(window, 0, TUNNEL_WIDTH - 1, ACS_URCORNER);

//        mvwaddch(window, TUNNEL_HEIGHT - 1, 0, ACS_LLCORNER);
        for (int x = 1; x < TUNNEL_WIDTH - 1; ++x) {
            mvwaddch(window, TUNNEL_HEIGHT - 1, x, ACS_HLINE);
        }
//        mvwaddch(window, TUNNEL_HEIGHT - 1, TUNNEL_WIDTH - 1, ACS_LRCORNER);
    }
};

#endif //OFFICE_EMPLOYEEANIMATION_HPP
