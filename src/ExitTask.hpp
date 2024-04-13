#ifndef OFFICE_EXITTAST_H
#define OFFICE_EXITTAST_H

#include <iostream>
#include "config/config.hpp"

class ExitTask {
public:
    static void exit_task();
};


void ExitTask::exit_task() {
    while (true) {
        int input_char = getchar();
        if (input_char == ' ') {
            program_running = false;
            break;
        }
    }
}

#endif //OFFICE_EXITTAST_H