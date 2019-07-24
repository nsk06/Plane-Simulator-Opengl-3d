#include "ring.h"
#include "main.h"
using namespace std;
Ring::Ring(double x, double y, double z) {
    this->position = glm::vec3(x, y, z);
    this->type = 0;
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Ring has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat _data[1000];
    int n = 50;
    double pi = 3.14;
    int i=0;
    for(i=0;i<n;i++) {
          _data[9*i] = 2.5*cos(2*pi*i/n);
          _data[9*i+1] = 2.5*sin(2*pi*i/n);
          _data[9*i+2] = 0;
          _data[9*i+3] = 2.5*cos(2*pi*(i+1)/n);
          _data[9*i+4] = 2.5*sin(2*pi*(i+1)/n);
          _data[9*i+5] = 0;
          _data[9*i+6] = 0;
          _data[9*i+7] = 0;
          _data[9*i+8] = 0;
    }  
    this->base = Cylinder(this->position.x,this->position.y,this->position.z,2.5,.6,COLOR_Silver);
    this->base.rotationx = -90;
    this->object = create3DObject(GL_TRIANGLES,3*n,_data,COLOR_WHITE,GL_LINE);  
}

void Ring::draw(glm::mat4 VP) {
    this->base.draw(VP);
    Matrices.model = glm::mat4(1.0);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0, 1));
    // No need as coords centered at 0, 0, 0 of Ring arouund which we waant to rotate
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

void Ring::set_position(double x, double y,double z) {
    this->position = glm::vec3(x, y, z);
}
void Ring::tick()
{
    this->rotation += 1;
}