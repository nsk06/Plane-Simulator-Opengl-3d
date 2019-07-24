#include "main.h"
#include "cylinder.h"
#include "cone.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 shoot_dir;
    float rotation;
    float rotationx;
    float rotationy;
    float timer;
    int type;
    float speed;
    float yspeed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *base1;
    VAO *base2;
    VAO *top;
    VAO *back;
};

#endif // Island_H
