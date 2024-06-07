#ifndef OFFICE_EXITSERVICE_HPP
#define OFFICE_EXITSERVICE_HPP

#include "../config/config.hpp"

class ExitService {
private:
    thread exit_thread;

    static void exit_task();

    void create_thread();

public:

    void join_thread();

    void run();
};

void ExitService::exit_task() {
    while (true) {
        int input_char = getchar();
        if (input_char == ' ') {
            program_running = false;
            cv_elevator_exit.notify_all();
            cv_elevator_enter.notify_all();
            exit_condition_variable.notify_all();
            break;
        }
    }
}

void ExitService::join_thread() {
    exit_thread.join();
}

void ExitService::create_thread() {
    exit_thread = std::thread([]() -> void {
        exit_task();
    });
}

void ExitService::run() {
    create_thread();
}

#endif //OFFICE_EXITSERVICE_HPP
