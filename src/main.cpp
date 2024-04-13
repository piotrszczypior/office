#include <ncurses.h>
#include <string>
#include <thread>
#include <mutex>
#include "config/config.hpp"
#include "ExitTask.hpp"
#include "model/Employee.hpp"
#include "Simulation.hpp"

using namespace std;

void init_library() {
    initscr();
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
}

WINDOW *print_shaft() {
    const int start_y = 3;
    const int start_x = (COLS - SHAFT_WIDTH) / 2;

    WINDOW *elevator_shaft = newwin(SHAFT_HEIGHT, SHAFT_WIDTH, start_y, start_x);

    box(elevator_shaft, 0, 0);
    wrefresh(elevator_shaft);
    return elevator_shaft;
}

WINDOW *print_third_floor_exit() {
    const int start_y = 3;
    const int start_x = 60;

    WINDOW *third_floor_exit = newwin(EMPLOYEE_EXIT_HEIGHT, EMPLOYEE_EXIT_WIDTH, start_y, start_x);

    for (int x = 0; x < EMPLOYEE_EXIT_WIDTH; ++x) {
        mvwaddch(third_floor_exit, 0, x, ACS_HLINE);
    }

    for (int y = 0; y < EMPLOYEE_EXIT_HEIGHT; ++y) {
        mvwaddch(third_floor_exit, y, 0, ACS_VLINE);
    }

    for (int x = 0; x < EMPLOYEE_EXIT_WIDTH; ++x) {
        mvwaddch(third_floor_exit, EMPLOYEE_EXIT_HEIGHT - 1, x, ACS_HLINE);
    }

    mvwaddch(third_floor_exit, 0, 0, ACS_ULCORNER);
    mvwaddch(third_floor_exit, EMPLOYEE_EXIT_HEIGHT - 1, 0, ACS_LLCORNER);
    mvwaddch(third_floor_exit, 0, EMPLOYEE_EXIT_WIDTH - 1, ACS_URCORNER);
    mvwaddch(third_floor_exit, EMPLOYEE_EXIT_HEIGHT - 1, EMPLOYEE_EXIT_WIDTH - 1, ACS_LRCORNER);

    wrefresh(third_floor_exit);
    return third_floor_exit;
}


void draw_exit_window() {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    const int height = 3;
    const int width = 30;
    const int start_x = (COLS - width) / 2;

    WINDOW *exit_window = newwin(height, width, 0, start_x);
    std::lock_guard<std::mutex> writing_lock(mx_drawing);
    wattron(exit_window, COLOR_PAIR(1));
    box(exit_window, 0, 0);
    wattroff(exit_window, COLOR_PAIR(1));

    const string message = "Press SPACE to exit";
    mvwprintw(exit_window, height / 2, (width - message.size()) / 2, "%s", message.c_str());

    wrefresh(exit_window);
}

int main() {
    init_library();

    std::thread exit_thread(&ExitTask::exit_task);

    Employee ele = Employee()
            .set_color(1)
            .set_employee_name("d")
            .set_position_x(1)
            .set_position_y(2);

    draw_exit_window();
    WINDOW *shaft = print_shaft();
//    WINDOW *office_exit = print_third_floor_exit();

    Elevator elevator = Elevator()
            .set_current_floor(3)
            .set_position_y(1)
            .set_position_x(1);

    auto elevatorAnimation = ElevatorAnimation(shaft);
    Simulation simulation = Simulation(elevatorAnimation, elevator);
    simulation.run();

    exit_thread.join();
    endwin();
    return 0;
}
