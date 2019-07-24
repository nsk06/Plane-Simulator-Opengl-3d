#include "main.h"

#ifndef SPHERE
#define SPHERE


class Sphere {
public:
   Sphere() {}
    Sphere(double x, double y,double z,float radius, color_t color);
    glm::vec3 position;
    double rotationx;
    double rotationy;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    void tick();
    int type;
    float timer;
    double speed;
    double yspeed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};
#endif // Island_H