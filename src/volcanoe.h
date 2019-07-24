#include "main.h"
#include "cone.h"
#ifndef VOLCANOE_H
#define VOLCANOE_H

class Volcanoe {
public:
    Volcanoe() {}
    Volcanoe(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    Cone mount;
    long long int timer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *base;
};

#endif // Island_H
