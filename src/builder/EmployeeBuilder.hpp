#ifndef OFFICE_EMPLOYEEBUILDER_HPP
#define OFFICE_EMPLOYEEBUILDER_HPP

#include <random>
#include <ncurses.h>

#include "../model/Employee.hpp"
#include "../config/config.hpp"

class EmployeeBuilder {
private:
    std::random_device random_device;
    std::mt19937 generator{random_device()};
    std::uniform_int_distribution<> position_y_distribution{-1, 1};
    std::uniform_int_distribution<> speed_distribution{1, 5};
    std::uniform_int_distribution<> name_distribution{'A', 'Z'};
    std::uniform_int_distribution<> color_distribution{0, 12};

public:
    Employee build() {
        int random_speed = speed_distribution(generator);
        char random_char = static_cast<char>(name_distribution(generator));
        std::string random_name = std::string(1, random_char);

        return Employee()
                .set_position_x(ENTRY_TUNNEL_X + 1)
                .set_position_y(ENTRY_TUNNEL_Y + TUNNEL_HEIGHT / 2 + position_y_distribution(generator))
                .set_employee_name(random_name)
                .set_color(color_distribution(generator))
                .set_speed(random_speed);
    }
};


#endif //OFFICE_EMPLOYEEBUILDER_HPP
