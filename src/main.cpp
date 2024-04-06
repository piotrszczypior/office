#include <ncurses.h>
#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include "Elevator.h"
#include "config.h"

using namespace std;

mutex mtx;
atomic<bool> program_running(true);

WINDOW *initialize_exit_window() {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    const int height = 3;
    const int width = 30;
    const int startx = (COLS - width) / 2;

    WINDOW *exit_window = newwin(height, width, 0, startx);
    std::lock_guard<std::mutex> writing_lock(mx_drawing);
    wattron(exit_window, COLOR_PAIR(1));
    box(exit_window, 0, 0);
    wattroff(exit_window, COLOR_PAIR(1));

    const string message = "Press SPACE to exit";
    mvwprintw(exit_window, height / 2, (width - message.size()) / 2, "%s", message.c_str());

    wrefresh(exit_window);
    return exit_window;
}

void exit_task() {
    WINDOW *exit_window = initialize_exit_window();

    while (true) {
        int input_char = wgetch(exit_window);
        if (input_char == ' ') {
            program_running = false;
            break;
        }
    }
    delwin(exit_window);
}

void draw_rectangle(WINDOW *win, int y, int x, int height, int width) {

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                mvwaddch(win, y + i, x + j, '*');
            } else {
                mvwaddch(win, y + i, x + j, ' ');
            }
        }
    }
    wrefresh(win);
}

void animate_rectangle() {
    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    WINDOW *elevator_shaft = newwin(LINES - 3, COLS, 3, 0);

    int rect_height = 3, rect_width = 10;
    int start_y = (max_y - rect_height) / 2;

    while (program_running) {
        for (int start_x = 0; start_x <= max_x - rect_width; ++start_x) {
            if (!program_running) break;
            std::lock_guard<std::mutex> writing_lock(mx_drawing);
            werase(elevator_shaft);
            draw_rectangle(elevator_shaft, start_y, start_x, rect_height, rect_width);
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
}


int main() {
    initscr();
    if (stdscr == nullptr) {
        return -1;
    }
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    thread t1(exit_task);
    thread t2(animate_rectangle);

    Elevator elevator;
    elevator.draw_elevator();

    t1.join();
    t2.join();

    endwin();
    return 0;
}
