#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y,float z,color_t color);
    glm::vec3 position;
    glm::vec3 axes_of_rotation;
    glm::vec4 target_dir;
    float rotationz;
    float rotationy;
    float rotationx;
    float rotation;
    float timer;
    int powertime;
    int score;
    int keypress;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *mid1;
    VAO *mid2;
    VAO *back;
    VAO *front; 
    VAO *flag;    
    VAO *fire;
    VAO *target;
    VAO *power;    
};

#endif // BALL_H
