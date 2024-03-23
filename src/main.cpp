#include <ncurses.h>
#include <string>
#include <iostream>

using namespace std;

WINDOW* initialize_exit_window() {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    const int height = 3;
    const int width = 30;
    const int startx = (COLS - width) / 2;

    WINDOW *exit_window = newwin(height, width, 0, startx);

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
    start_color();
    noecho();
    cbreak();
    curs_set(0);

    WINDOW* exit_window = initialize_exit_window();

    while (true) {
        int input_char = wgetch(exit_window);
        if (input_char == ' ') {
            break;
        }
    }

    endwin();
    return 0;
}
