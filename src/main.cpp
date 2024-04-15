#include <ncurses.h>
#include <string>
#include <thread>
#include <mutex>
#include "config/config.hpp"
#include "ExitTask.hpp"
#include "model/Employee.hpp"
#include "SimulationService.hpp"

using namespace std;

void init_library() {
    initscr();
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();

}

void init_colors() {
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_RED);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLUE);
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_RED, COLOR_WHITE);
    init_pair(10, COLOR_BLACK, COLOR_YELLOW);
    init_pair(11, COLOR_YELLOW, COLOR_BLACK);
    init_pair(12, COLOR_CYAN, COLOR_BLACK);
    init_pair(13, COLOR_RED, COLOR_BLACK);
}

WINDOW *print_shaft() {
    const int start_y = 3;
    const int start_x = (COLS - SHAFT_WIDTH) / 2;

    WINDOW *elevator_shaft = newwin(SHAFT_HEIGHT, SHAFT_WIDTH, start_y, start_x);

    box(elevator_shaft, 0, 0);
    wrefresh(elevator_shaft);
    return elevator_shaft;
}

void draw_exit_window() {
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
    init_colors();

    std::thread exit_thread(&ExitTask::exit_task);

    draw_exit_window();
    WINDOW *shaft = print_shaft();

    EmployeeAnimation::print_floor_tunnel(ENTRY_TUNNEL_X, ENTRY_TUNNEL_Y);
    EmployeeAnimation::print_floor_tunnel(EXIT_TUNNEL_X, FIRST_FLOOR + ELEVATOR_HEIGHT / 2);
    EmployeeAnimation::print_floor_tunnel(EXIT_TUNNEL_X, SECOND_FLOOR + ELEVATOR_HEIGHT / 2);
    EmployeeAnimation::print_floor_tunnel(EXIT_TUNNEL_X, THIRD_FLOOR + ELEVATOR_HEIGHT / 2);

    Elevator elevator = Elevator()
            .set_current_floor(3)
            .set_position_y(1)
            .set_position_x(1);

    auto elevatorAnimation = ElevatorAnimation(shaft);
    SimulationService simulation = SimulationService(elevatorAnimation, elevator);
    simulation.run();

    exit_thread.join();

    endwin();
    return 0;
}
