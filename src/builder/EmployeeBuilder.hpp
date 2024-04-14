#ifndef OFFICE_EMPLOYEEBUILDER_HPP
#define OFFICE_EMPLOYEEBUILDER_HPP

#include <random>
#include <ncurses.h>

#include "../model/Employee.hpp"
#include "../config/config.hpp"

class EmployeeBuilder {
private:

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> speed_dist{1, 5};
    std::uniform_int_distribution<> name_dist{'A', 'Z'};
    std::uniform_int_distribution<> color_dist{0, 2};

public:
    Employee build() {
        int random_speed = speed_dist(gen);
        char random_char = static_cast<char>(name_dist(gen));
        std::string random_name = std::string(1, random_char);


        return Employee()
                .set_position_x(ENTRY_TUNNEL_X + 1)
                .set_position_y(ENTRY_TUNNEL_Y + TUNNEL_HEIGHT / 2)
                .set_employee_name(random_name)
                .set_color(color_dist(gen))
                .set_speed(random_speed);
    }
};


#endif //OFFICE_EMPLOYEEBUILDER_HPP
