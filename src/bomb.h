#include "main.h"
#include "sphere.h"

#ifndef Bomb_H
#define Bomb_H

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float timer;
    float speed;
    Sphere blast;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *base1;
};

#endif // Island_H
