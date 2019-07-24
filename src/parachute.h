#include "main.h"
#include "cuboid.h"
#ifndef Parachute_H
#define Parachute_H
class Parachute {
public:
   Parachute() {}
    Parachute(double x, double y,double z);
    glm::vec3 position;
    double rotation;
    int type;
    int timer;
    Cuboid goodies[4];
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    void tick();
private:
    VAO *object;
    VAO *object2;
    VAO *head;
    VAO *legs;
    VAO *shoes;
    VAO *face;
    VAO *rop;
    VAO *health;
    VAO *swordA;
    VAO *swordB;
};

#endif // Island_H
