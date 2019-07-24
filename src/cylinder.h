#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y,float z,float radius , float height , color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 dimensions;
    float rotation;
    float rotationx;
    float rotationy;
    float rotationz;
    bool rot_dir;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object1;
    VAO *object2;
};
#endif // Island_H