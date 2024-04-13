#include <ncurses.h>
#include <string>
#include <thread>
#include <mutex>
#include "config/config.hpp"
#include "ExitTask.hpp"
#include "model/Employee.hpp"
#include "Simulation.hpp"

void animate_elevator(WINDOW *shaft, Elevator &elevator);

using namespace std;


//
//void draw_rectangle(WINDOW *win, int y, int x, int height, int width) {
//    for (int i = 0; i < height; ++i) {
//        for (int j = 0; j < width; ++j) {
//            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
//                mvwaddch(win, y + i, x + j, '*');
//            } else {
//                mvwaddch(win, y + i, x + j, ' ');
//            }
//        }
//    }
//    wrefresh(win);
//}

//void animate_rectangle() {
//    int max_x, max_y;
//    getmaxyx(stdscr, max_y, max_x);
//    init_pair(1, COLOR_BLUE, COLOR_BLACK);
//    const int height = 35;
//    const int width = 15;
//    const int start_y = 4;
//    const int start_x = (COLS - width) / 2 + 3;
//
//
//    WINDOW *elevator_shaft = newwin(height, width, start_y, start_x);
//    box(elevator_shaft, 0, 0);
//    int rect_height = 3, rect_width = 10;
////    int start_x = (max_x - rect_width) / 2;
//
//    while (program_running.load()) {
//        for (int y = 0; y <= max_y - rect_height; ++y) {
//            if (!program_running) {
//                break;
//            }
//            std::lock_guard<std::mutex> writing_lock(mx_drawing);
//            werase(elevator_shaft);
//            draw_rectangle(elevator_shaft, y, start_x, rect_height, rect_width);
//            wrefresh(elevator_shaft);
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        }
//    }
//}


WINDOW *print_shaft() {
    const int height = 40;
    const int width = 20;
    const int start_y = 3;
    const int start_x = (COLS - width) / 2;

    WINDOW *elevator_shaft = newwin(height, width, start_y, start_x);

    std::lock_guard<std::mutex> writing_lock(mx_drawing);
    box(elevator_shaft, 0, 0);
    wrefresh(elevator_shaft);
    return elevator_shaft;
}


WINDOW *initialize_exit_window() {
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
    return exit_window;
}

int main() {
    initscr();
    if (stdscr == nullptr) {
        return -1;
    }
    nodelay(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    std::thread exit_thread(&ExitTask::exit_task);

    Employee ele = Employee()
            .set_color(1)
            .set_employee_name("d")
            .set_position_x(1)
            .set_position_y(2);

    initialize_exit_window();
    WINDOW *shaft = print_shaft();

    Elevator elevator = Elevator()
            .set_current_floor(3)
            .set_position_y(1)
            .set_position_x(1);
//    ElevatorAnimation elevatorAnimation = ElevatorAnimation(elevator, shaft);
    auto elevatorAnimation = ElevatorAnimation(shaft);
    Simulation simulation = Simulation(elevatorAnimation, elevator);
    simulation.run();

//    animate_elevator(shaft, simulation.elevator);

//    while (program_running.load()) {
//        WINDOW *shaft = print_shaft();
//        animate_elevator(shaft);
//        wrefresh(shaft);
//        delwin(shaft);
//    }

    exit_thread.join();
    endwin();
    return 0;
}

void animate_elevator(WINDOW *shaft, Elevator &elevator) {
    int max_y, max_x;
    getmaxyx(shaft, max_y, max_x); // Get the height and width of the elevator shaft window

    int elevator_height = 3; // Height of the elevator
    int elevator_width = max_x - 2; // Width of the elevator, accounting for window borders
    int elevator_start_y = 1; // Starting y-position of the elevator
    int elevator_start_x = 1; // Starting x-position of the elevator (inside the shaft borders)

    std::string inside_message = "Elevator";

    while (program_running.load()) {
        std::lock_guard<std::mutex> writing_lock(mx_drawing);

        // Clear previous position
        werase(shaft);

        // Redraw the shaft borders
        box(shaft, 0, 0);

        // Draw the elevator at the new position
        for (int y = elevator.get_position_y(); y < elevator.get_position_y() + elevator_height; ++y) {
            mvwhline(shaft, y, elevator_start_x, ' ' | A_REVERSE, elevator_width);
        }

        int message_start_x = elevator_start_x + (elevator_width - inside_message.length()) / 2;
        // Calculate the y-position for the message to be vertically centered inside the elevator
        int message_y = elevator.get_position_y() + elevator_height / 2;
        mvwprintw(shaft, message_y, message_start_x, "%s", inside_message.c_str());


        // Refresh the shaft window to update the drawing
        wrefresh(shaft);

        // Sleep for a short duration to control the speed of the elevator animation
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}