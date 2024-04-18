#ifndef OFFICE_EMPLOYEEBUILDER_HPP
#define OFFICE_EMPLOYEEBUILDER_HPP

#include <random>
#include <ncurses.h>

#include "../model/Employee.hpp"
#include "../config/config.hpp"

class EmployeeBuilder {
private:
    static int generate_random_speed() {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> speed_distribution(1, 5);
        return speed_distribution(generator);
    }

    static char generate_random_name() {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> name_distribution('A', 'Z');
        return static_cast<char>(name_distribution(generator));
    }

    static int generate_random_position_y() {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> position_y_distribution(-1, 1);
        return position_y_distribution(generator);
    }

    static int generate_random_color() {
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> color_distribution(0, 12);
        return color_distribution(generator);
    }

public:
    static Employee build() {
        return Employee()
                .set_position_x(ENTRY_TUNNEL_X + 1)
                .set_position_y(ENTRY_TUNNEL_Y + TUNNEL_HEIGHT / 2 + generate_random_position_y())
                .set_employee_name(generate_random_name())
                .set_color(generate_random_color())
                .set_speed(generate_random_speed());
    }
};


#endif //OFFICE_EMPLOYEEBUILDER_HPP
