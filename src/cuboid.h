#include "main.h"

#ifndef CUBOID
#define CUBOID


class Cuboid {
public:
    Cuboid() {}
    Cuboid(float x, float y,float z,float width , float height , float depth,  color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 dimensions;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};
#endif // Island_H