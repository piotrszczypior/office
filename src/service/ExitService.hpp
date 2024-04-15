#ifndef OFFICE_EXITSERVICE_HPP
#define OFFICE_EXITSERVICE_HPP

#include "../config/config.hpp"

class ExitService {
public:
    static void exit_task();
};

void ExitService::exit_task() {
    while (true) {
        int input_char = getchar();
        if (input_char == ' ') {
            program_running = false;
            break;
        }
    }
}

#endif //OFFICE_EXITSERVICE_HPP
