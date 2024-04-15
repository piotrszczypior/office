#ifndef OFFICE_MAP_HPP
#define OFFICE_MAP_HPP

#include "../config/config.hpp"

#include <string>
#include <map>
#include <mutex>

using namespace std;

class Map {
private:
    std::map<std::string, bool> occupiedPositions;

public:
    static std::string makeKey(int x, int y) {
        return std::to_string(x) + "," + std::to_string(y);
    }

    bool isPositionFree(int x, int y) {
        std::lock_guard<std::mutex> lock(mx_positions);
        auto key = makeKey(x, y);
        return occupiedPositions.find(key) == occupiedPositions.end();
    }

    void occupyPosition(int x, int y) {
        std::lock_guard<std::mutex> lock(mx_positions);
        occupiedPositions[makeKey(x, y)] = true;
    }

    void freePosition(int x, int y) {
        std::lock_guard<std::mutex> lock(mx_positions);
        occupiedPositions.erase(makeKey(x, y));
    }
};

#endif //OFFICE_MAP_HPP
