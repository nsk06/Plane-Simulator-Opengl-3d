#include "main.h"
#include "cylinder.h"
#ifndef Ring_H
#define Ring_H
class Ring {
public:
   Ring() {}
    Ring(double x, double y,double z);
    glm::vec3 position;
    double rotation;
    int type;
    Cylinder base;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    void tick();
private:
    VAO *object;
};

#endif // Island_H
