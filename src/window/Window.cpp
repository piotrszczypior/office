#include "Window.hpp"
#include <string>
#include <iostream>

void Window::redraw_employee(const shared_ptr<Employee> &employee) {
    if (employee->is_inside_elevator()) {
        return;
    }
    attron(COLOR_PAIR(employee->get_color()));
    mvaddch(employee->get_position_y(), employee->get_position_x(), employee->get_employee_name());
    attroff(COLOR_PAIR(employee->get_color()));
}

void Window::redraw_elevator() {
    std::string inside_message;
    Elevator elevator = state.get_elevator();

    for (const auto &employee: state.get_employees()) {
        if (employee->is_inside_elevator())
            inside_message += string(1, employee->get_employee_name()) + " ";
    }

    if (inside_message.empty()) {
        inside_message = "Elevator empty";
    }

    for (int y = elevator.get_position_y(); y < elevator.get_position_y() + ELEVATOR_HEIGHT; ++y) {
        mvhline(elevator.get_position_y(), elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_HEIGHT);
        mvhline(elevator.get_position_y(), elevator.get_position_x(), ' ' | A_REVERSE, ELEVATOR_WIDTH);
        mvhline(elevator.get_position_y() + ELEVATOR_HEIGHT - 1, elevator.get_position_x(), ' ' | A_REVERSE,
                ELEVATOR_WIDTH);
    }

    int message_start_x = elevator.get_position_x() + (ELEVATOR_WIDTH - inside_message.length()) / 2;
    int message_y = elevator.get_position_y() + ELEVATOR_HEIGHT / 2;
    mvprintw(message_y, message_start_x, "%s", inside_message.c_str());
}

void Window::print_shaft() {
    const int start_y = 3;
    const int start_x = (COLS - SHAFT_WIDTH) / 2;

    // TOP border
    for (int x = 1; x < TUNNEL_WIDTH + SHAFT_WIDTH - 1; ++x) {
        mvaddch(ENTRY_TUNNEL_Y, ENTRY_TUNNEL_X + x, ACS_HLINE);
    }
    // ENTRY bottom border
    for (int x = 1; x < TUNNEL_WIDTH; ++x) {
        mvaddch(ENTRY_TUNNEL_Y + TUNNEL_HEIGHT - 1, ENTRY_TUNNEL_X + x, ACS_HLINE);
    }
    // corrner
    mvaddch(ENTRY_TUNNEL_Y + TUNNEL_HEIGHT - 1, ENTRY_TUNNEL_X + TUNNEL_WIDTH, ACS_URCORNER);

    // left border
    for (int y = TUNNEL_HEIGHT; y < SHAFT_HEIGHT; ++y) {
        mvaddch(start_y + y, start_x, ACS_VLINE);
    }

    // Upper-right corner
    mvaddch(start_y, start_x + SHAFT_WIDTH - 1, ACS_URCORNER);

    // before First floor right border
    for (int y = 1; y < FIRST_FLOOR - ELEVATOR_HEIGHT / 2; ++y) {
        mvaddch(ENTRY_TUNNEL_Y + y, EXIT_TUNNEL_X, ACS_VLINE);
    }

    // first floor top corner
    mvaddch(FIRST_FLOOR + 1, EXIT_TUNNEL_X, ACS_LLCORNER);
    // first floor bot corner
    mvaddch(FIRST_FLOOR + TUNNEL_HEIGHT, EXIT_TUNNEL_X, ACS_ULCORNER);

    // zwischen first and second floor
    for (int y = FIRST_FLOOR + ELEVATOR_HEIGHT * 2; y < SECOND_FLOOR + ELEVATOR_HEIGHT / 2; ++y) {
        mvaddch(y, EXIT_TUNNEL_X, ACS_VLINE);
    }

    // second floor top corner
    mvaddch(SECOND_FLOOR + 1, EXIT_TUNNEL_X, ACS_LLCORNER);
    // second floor bot corner
    mvaddch(SECOND_FLOOR + TUNNEL_HEIGHT, EXIT_TUNNEL_X, ACS_ULCORNER);

    // zwischen second and third floor
    for (int y = SECOND_FLOOR + ELEVATOR_HEIGHT * 2; y < THIRD_FLOOR + ELEVATOR_HEIGHT / 2; ++y) {
        mvaddch(y, EXIT_TUNNEL_X, ACS_VLINE);
    }

    // right under third floor
    for (int y = THIRD_FLOOR + ELEVATOR_HEIGHT * 2; y < SHAFT_HEIGHT - 1 + ENTRY_TUNNEL_Y; ++y) {
        mvaddch(y, EXIT_TUNNEL_X, ACS_VLINE);
    }

    // third floor top corner
    mvaddch(THIRD_FLOOR + 1, EXIT_TUNNEL_X, ACS_LLCORNER);
    // third floor bot corner
    mvaddch(THIRD_FLOOR + TUNNEL_HEIGHT, EXIT_TUNNEL_X, ACS_ULCORNER);

    // bottom border
    for (int x = 0; x < SHAFT_WIDTH; ++x) {
        mvaddch(start_y + SHAFT_HEIGHT - 1, start_x + x, ACS_HLINE);
    }

    // Lower-left corner
    mvaddch(start_y + SHAFT_HEIGHT - 1, start_x, ACS_LLCORNER);
    // Lower-right corner
    mvaddch(start_y + SHAFT_HEIGHT - 1, start_x + SHAFT_WIDTH - 1, ACS_LRCORNER);
}

void Window::draw_exit_window() {
    const int height = 3;
    const int width = 30;
    const int start_x = (COLS - width) / 2;
    const int start_y = 0;

    attron(COLOR_PAIR(1));

    for (int x = start_x; x < start_x + width; ++x) {
        mvaddch(start_y, x, ACS_HLINE);
        mvaddch(start_y + height - 1, x, ACS_HLINE);
    }

    for (int y = start_y; y < start_y + height; ++y) {
        mvaddch(y, start_x, ACS_VLINE);
        mvaddch(y, start_x + width - 1, ACS_VLINE);
    }

    mvaddch(start_y, start_x, ACS_ULCORNER);
    mvaddch(start_y, start_x + width - 1, ACS_URCORNER);
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    mvaddch(start_y + height - 1, start_x + width - 1, ACS_LRCORNER);

    attroff(COLOR_PAIR(1));

    std::string message = "Press SPACE to exit";
    mvprintw(start_y + height / 2, start_x + (width - message.size()) / 2, "%s", message.c_str());
}


void Window::draw_employees_in_elevator_banner() {
    const int height = 3;
    const int width = 30;
    const int start_x = (COLS - width) / 2 + 30;
    const int start_y = 0;

    attron(COLOR_PAIR(5));

    for (int x = start_x; x < start_x + width; ++x) {
        mvaddch(start_y, x, ACS_HLINE);
        mvaddch(start_y + height - 1, x, ACS_HLINE);
    }

    for (int y = start_y; y < start_y + height; ++y) {
        mvaddch(y, start_x, ACS_VLINE);
        mvaddch(y, start_x + width - 1, ACS_VLINE);
    }

    mvaddch(start_y, start_x, ACS_ULCORNER);
    mvaddch(start_y, start_x + width - 1, ACS_URCORNER);
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    mvaddch(start_y + height - 1, start_x + width - 1, ACS_LRCORNER);

    attroff(COLOR_PAIR(5));

    std::string message = "Employees in elevator: " + to_string(state.employees_in_elevator);
    mvprintw(start_y + height / 2, start_x + (width - message.size()) / 2, "%s", message.c_str());
}


void Window::draw_employees_limit_banner() {
    const int height = 3;
    const int width = 30;
    const int start_x = (COLS - width) / 2 - 30;
    const int start_y = 0;

    attron(COLOR_PAIR(11));

    for (int x = start_x; x < start_x + width; ++x) {
        mvaddch(start_y, x, ACS_HLINE);
        mvaddch(start_y + height - 1, x, ACS_HLINE);
    }

    for (int y = start_y; y < start_y + height; ++y) {
        mvaddch(y, start_x, ACS_VLINE);
        mvaddch(y, start_x + width - 1, ACS_VLINE);
    }

    mvaddch(start_y, start_x, ACS_ULCORNER);
    mvaddch(start_y, start_x + width - 1, ACS_URCORNER);
    mvaddch(start_y + height - 1, start_x, ACS_LLCORNER);
    mvaddch(start_y + height - 1, start_x + width - 1, ACS_LRCORNER);

    attroff(COLOR_PAIR(11));

    std::string message = "Limit in elevator: " + to_string(MAX_EMPLOYEE_IN_ELEVATOR + 1);
    mvprintw(start_y + height / 2, start_x + (width - message.size()) / 2, "%s", message.c_str());
}

void Window::print_floor_tunnel(int position_x, int position_y) {
    for (int x = 1; x < TUNNEL_WIDTH - 1; ++x) {
        mvaddch(position_y, position_x + x, ACS_HLINE);
        mvaddch(position_y + TUNNEL_HEIGHT - 1, position_x + x, ACS_HLINE);
    }
}

void Window::draw_floor_counter(int position_x, int position_y, int number) {
    attron(COLOR_PAIR(2));
    int number_of_digits = std::to_string(std::abs(number)).length();

    int width = number_of_digits % 2 == 1 ? 11 : 10;

    for (int x = 0; x < width; ++x) {
        mvaddch(position_y, position_x + x, ACS_HLINE);
        mvaddch(position_y + 4, position_x + x, ACS_HLINE);
    }

    for (int y = 0; y < 5; ++y) {
        mvaddch(position_y + y, position_x, ACS_VLINE);
        mvaddch(position_y + y, position_x + width - 1, ACS_VLINE);
    }

    mvaddch(position_y, position_x, ACS_ULCORNER);
    mvaddch(position_y, position_x + width - 1, ACS_URCORNER);
    mvaddch(position_y + 4, position_x, ACS_LLCORNER);
    mvaddch(position_y + 4, position_x + width - 1, ACS_LRCORNER);

    attroff(COLOR_PAIR(2));
    int midX = (width / 2) + position_x;
    midX -= number_of_digits / 2;
    int midY = position_y + 2;

    mvprintw(midY, midX, "%d", number);
}

void Window::create_ui() {
    while (program_running) {
        clear();
        draw_exit_window();
        draw_employees_in_elevator_banner();
        draw_employees_limit_banner();

        print_shaft();
        print_floor_tunnel(EXIT_TUNNEL_X, FIRST_FLOOR + ELEVATOR_HEIGHT / 2);
        print_floor_tunnel(EXIT_TUNNEL_X, SECOND_FLOOR + ELEVATOR_HEIGHT / 2);
        print_floor_tunnel(EXIT_TUNNEL_X, THIRD_FLOOR + ELEVATOR_HEIGHT / 2);

        draw_floor_counter(EXIT_TUNNEL_X + TUNNEL_WIDTH, FIRST_FLOOR + ELEVATOR_HEIGHT / 2, state.get_record()[2]);
        draw_floor_counter(EXIT_TUNNEL_X + TUNNEL_WIDTH, SECOND_FLOOR + ELEVATOR_HEIGHT / 2, state.get_record()[1]);
        draw_floor_counter(EXIT_TUNNEL_X + TUNNEL_WIDTH, THIRD_FLOOR + ELEVATOR_HEIGHT / 2, state.get_record()[0]);

        redraw_elevator();

        for (const auto &employee: state.get_employees()) {
            redraw_employee(employee);
        }
        refresh();
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}
