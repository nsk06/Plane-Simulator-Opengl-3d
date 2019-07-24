#include "main.h"
#include "cuboid.h"
#include "cylinder.h"
#include "sphere.h"

#ifndef Boat_Enemy_H
#define Boat_Enemy_H
class Boat_Enemy {
public:
    Boat_Enemy() {}
    Boat_Enemy(float x, float y, float z);
    glm::vec3 position;
    float speed;
    float rotation;
    Cuboid structure[5];
    Cylinder Cannon;
    Cylinder Cannon2;
    int type ;
    int timer ;
    bool start_fire;
    std::vector<Sphere>cannonballs;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *front;
};

#endif // Boat_Enemy_H
