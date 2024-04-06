#include "Elevator.h"
#include "mutex"
#include "../config/config.h"

void Elevator::draw_elevator() {
    int max_x, max_y;
    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    getmaxyx(stdscr, max_y, max_x);
    int window_width = 20;
    int window_height = 10;
    int start_x = (max_x - window_width) / 2;
    int start_y = 0;

    elevator_window = newwin(window_height, window_width, start_y, start_x);

    std::lock_guard<std::mutex> writing_lock(mx_drawing);

    box(elevator_window, 0 , 0);

    wattron(elevator_window, COLOR_PAIR(1));
    wattroff(elevator_window, COLOR_PAIR(1));

    wrefresh(elevator_window);
}
