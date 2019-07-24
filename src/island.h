#include "main.h"
#include "cuboid.h"
#include "cylinder.h"
#include "sphere.h"
#include "cone.h"
#ifndef Island_H
#define Island_H

class Island {
public:
    Island() {}
    Island(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    Cuboid rocks[3];
    Cylinder cannons[3];
    Cone objects[4];
    std::vector<Sphere> fireballs;
    int lives;
    int type;
    long long int timer;
    bool start_fire;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *base;
    VAO *base2;
    VAO *canons;
    VAO *pointer;
};

#endif // Island_H
