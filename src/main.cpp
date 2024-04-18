#include <ncurses.h>
#include <thread>
#include "model/Employee.hpp"
#include "service/SimulationService.hpp"
#include "service/ExitService.hpp"
#include "window/Window.hpp"

#include "builder/ElevatorBuilder.hpp"

using namespace std;

void init_library() {
    initscr();
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    setlocale(LC_ALL, "");
    clear();
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


int main() {
    init_library();
    init_colors();

    Elevator elevator = ElevatorBuilder::build();

    ExitService exitService = ExitService();
    exitService.run();
    State state = State(elevator);
    Window window = Window(state);
    window.create_thread();
    SimulationService simulation = SimulationService(state);
    simulation.run();

    window.join_thread();
    exitService.join_thread();

    endwin();
    return 0;
}
