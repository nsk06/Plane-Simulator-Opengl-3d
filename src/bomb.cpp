#include "bomb.h"
#include "main.h"
using namespace std;
Bomb::Bomb(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->speed = .2;
    float pi = 3.14;
    static int n = 100;
    this->timer = 0;
    GLfloat g_vertex_buffer_data[1000];
    int i;  
    Sphere s =  Sphere(this->position.x,this->position.y,this->position.z,.5,COLOR_PURE);
    s.type = 1;
    this->blast = s;
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->blast.draw(VP);
}

void Bomb::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Bomb::tick(){
    this->blast.tick();
    this->set_position(this->blast.position.x,this->blast.position.y,this->blast.position.z);
}
