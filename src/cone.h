#include "main.h"

#ifndef CONE
#define CONE


class Cone {
public:
    Cone() {}
    Cone(float x, float y,float z,float radius , float height , color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 dimensions;
    float rotation;
    bool rot_dir;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};
#endif // Island_H