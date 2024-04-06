#ifndef CONFIG_H
#define CONFIG_H

#include <mutex>
#include <atomic>

extern std::mutex mx_drawing;
extern std::atomic<bool> program_running;

#endif // CONFIG_H