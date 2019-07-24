#include "main.h"

#ifndef Dashboard_H
#define Dashboard_H

class Dashboard {
public:
    Dashboard() {}
    Dashboard(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 scale_factor_altitude;
    glm::vec3 scale_factor_fuel;
    glm::vec3 scale_factor_speed;
    glm::vec3 scale_factor_health;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *altitude;
    VAO *fuel;
    VAO *speed;
    VAO *health;
    VAO *back;
};

#endif // Island_H
