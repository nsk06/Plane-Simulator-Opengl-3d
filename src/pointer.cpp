#include "pointer.h"
#include "main.h"
using namespace std;
Pointer::Pointer(double x, double y, double z) {
    this->position = glm::vec3(x, y, z);
    this->type = 0;
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Pointer has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat _data[1000];
    int n = 100;
    double pi = 3.14;
    int i=0; 
   GLfloat vertex_buffer_data[] = {
      .5,-.5,0,
      -.5,-.5,0,
      -.5,.5,0,
      -.5,.5,0,
      .5,.5,0,
      .5,-.5,0,

      .5,-.5,0,
      0,-.8,0,
      -.5,-.5,0,
  };
    this->object = create3DObject(GL_TRIANGLES,9, vertex_buffer_data,COLOR_RED, GL_FILL);
         
}

void Pointer::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of Pointer arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
   
}

void Pointer::set_position(double x, double y,double z) {
    this->position = glm::vec3(x, y, z);
}