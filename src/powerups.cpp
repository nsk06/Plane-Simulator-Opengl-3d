#include "powerups.h"
#include "main.h"
using namespace std;
Powerups::Powerups(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->speed = .2;
    float pi = 3.14;
    static int n = 100;
    this->timer = 0;
    GLfloat g_vertex_buffer_data[] = {
        -.5,0,0,
        -.5,.5,0,
        .5,.5,0,
        .5,.5,0,
        .5,0,0,
        -.5,0,0,

        -.5,.5,0,
        -.5,.8,0,
        -.3,.8,0,
        -.3,.8,0,
        -.3,.5,0,
        -.5,.5,0,

        -.3,.7,0,
        -.3,.8,0,
        .4,.8,0,
        .4,.8,0,
        .4,.7,0,
        -.3,.7,0,

        .4,.5,0,
        .4,.8,0,
        .5,.8,0,
        .5,.8,0,
        .5,.5,0,
        .4,.5,0,
    };
    this->bottle_shape = create3DObject(GL_TRIANGLES,24, g_vertex_buffer_data, COLOR_GOLD, GL_FILL);
}

void Powerups::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->bottle_shape);
}

void Powerups::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Powerups::tick(){
}
