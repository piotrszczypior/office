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

    std::lock_guard<std::mutex> writing_lock(mx_drawing);
    box(elevator_shaft, 0, 0);
    wrefresh(elevator_shaft);
    return elevator_shaft;
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
