#include "main.h"

#ifndef Pointer_H
#define Pointer_H
class Pointer {
public:
   Pointer() {}
    Pointer(double x, double y,double z);
    glm::vec3 position;
    double rotation;
    int type;
    void draw(glm::mat4 VP);
    void set_position(double x, double y ,double z);
    void tick();
private:
    VAO *object;
};

#endif // Island_H
