#ifndef CONFIG_H
#define CONFIG_H

#include <mutex>
#include <atomic>

#define FIRST_FLOOR 10
#define SECOND_FLOOR 20
#define THIRD_FLOOR 30

#define SHAFT_HEIGHT 40
#define SHAFT_WIDTH 20

#define ELEVATOR_WIDTH 18
#define ELEVATOR_HEIGHT 3

#define TUNNEL_WIDTH 36
#define TUNNEL_HEIGHT (ELEVATOR_HEIGHT + 2)
#define ENTRY_TUNNEL_X (COLS / 2 - TUNNEL_WIDTH - SHAFT_WIDTH / 2)
#define ENTRY_TUNNEL_Y 3

#define EXIT_TUNNEL_X (COLS / 2 + SHAFT_WIDTH / 2)

#define EMPLOYEE_NUMBER 4

inline std::mutex mx_drawing;
inline std::atomic<bool> program_running(true);
inline int FLOOR_POSITIONS[] = {THIRD_FLOOR, SECOND_FLOOR, FIRST_FLOOR};

#endif // CONFIG_H