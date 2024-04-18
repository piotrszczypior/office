#ifndef OFFICE_WINDOW_HPP
#define OFFICE_WINDOW_HPP


#include "../service/State.hpp"
#include "ncurses.h"
#include "../config/config.hpp"
#include <thread>

class Window {
private:
    State &state;
    thread ui_thread;

    void print_shaft();

    static void redraw_employee(const shared_ptr<Employee> &employee);

    void redraw_elevator();

    void create_ui();

    static void draw_exit_window();

    static void print_floor_tunnel(int position_x, int position_y);

public:
    explicit Window(State &state) : state(state) {};

    void create_thread() {
        ui_thread = std::thread([this]() -> void {
            create_ui();
        });
    };

    void join_thread() {
        ui_thread.join();
    }
};


#endif //OFFICE_WINDOW_HPP
