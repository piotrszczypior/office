//
// Created by piotr on 4/18/24.
//

#ifndef OFFICE_ELEVATORBUILDER_HPP
#define OFFICE_ELEVATORBUILDER_HPP

#include "../model/Elevator.hpp"
#include "../config/config.hpp"

class ElevatorBuilder {
public:
    static Elevator build() {
        return Elevator()
                .set_current_floor(3)
                .set_position_y(ELEVATOR_START_Y)
                .set_position_x(ELEVATOR_START_X);
    }
};

#endif //OFFICE_ELEVATORBUILDER_HPP
