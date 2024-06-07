#ifndef CONFIG_H
#define CONFIG_H

#include <mutex>
#include <atomic>
#include <condition_variable>

#define FIRST_FLOOR 10
#define SECOND_FLOOR 20
#define THIRD_FLOOR 30

#define SHAFT_HEIGHT 40
#define SHAFT_WIDTH 20

#define ELEVATOR_WIDTH 18
#define ELEVATOR_HEIGHT 3
#define ELEVATOR_START_Y 4
#define ELEVATOR_START_X (COLS / 2 - SHAFT_WIDTH / 2 + 1)


#define TUNNEL_WIDTH 36
#define TUNNEL_HEIGHT (ELEVATOR_HEIGHT + 2)
#define ENTRY_TUNNEL_X (COLS / 2 - TUNNEL_WIDTH - SHAFT_WIDTH / 2)
#define ENTRY_TUNNEL_Y 3

#define EXIT_TUNNEL_X (COLS / 2 + SHAFT_WIDTH / 2 - 1)

#define MAX_EMPLOYEE_IN_ELEVATOR 5

inline volatile bool program_running(true);
inline int FLOOR_POSITIONS[] = {THIRD_FLOOR, SECOND_FLOOR, FIRST_FLOOR};

inline std::mutex mx_elevator;

inline std::condition_variable cv_elevator_enter;
inline std::condition_variable cv_elevator_exit;
inline std::condition_variable exit_condition_variable;


#define MAX_NUMBER_OF_EMPLOYEES_EXITING_AT_ONCE 5
#define BREAK_IN_SECONDS 5

#endif // CONFIG_H