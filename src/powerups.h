#include "main.h"

#ifndef Powerups_H
#define Powerups_H

class Powerups {
public:
    Powerups() {}
    Powerups(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float timer;
    float speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *bottle_shape;
};

#endif // Island_H
