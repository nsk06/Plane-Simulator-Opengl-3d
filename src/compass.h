#include "main.h"

#ifndef Compass_H
#define Compass_H
class Circle {
public:
   Circle() {}
    Circle(double x, double y,double z,float radius, color_t color);
    glm::vec3 position;
    double rotation;
    int type;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    void tick();
private:
    VAO *object1;
    VAO *object2;
};
class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z);
    glm::vec3 position;
    glm::vec3 cplane_position;
    std::vector<glm::vec3> comp_positions;
    float rotation;
    float timer;
    float speed;
    Circle cpos[5];
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *base1;
    VAO *base2;
    VAO *plane_pos;
};


#endif // Island_H
