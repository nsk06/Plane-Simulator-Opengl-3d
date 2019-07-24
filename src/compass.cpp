#include "compass.h"
#include "main.h"
using namespace std;
Circle::Circle(double x, double y, double z,float radius, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->type = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Circle has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat _data[1000];
    int n = 100;
    double pi = 3.14;
    int i=0;
    for(i=0;i<n;i++) {
          _data[9*i] = radius*cos(2*pi*i/n);
          _data[9*i+1] = radius*sin(2*pi*i/n);
          _data[9*i+2] = 0;
          _data[9*i+3] = radius*cos(2*pi*(i+1)/n);
          _data[9*i+4] = radius*sin(2*pi*(i+1)/n);
          _data[9*i+5] = 0;
          _data[9*i+6] = 0;
          _data[9*i+7] = 0;
          _data[9*i+8] = 0;
    }   
       this->object1 = create3DObject(GL_TRIANGLES,3*n,_data,color,GL_FILL); 
       this->object2 = create3DObject(GL_TRIANGLES,3*n,_data,COLOR_Lime,GL_FILL);      
}

void Circle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of Circle arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->type == 0)
    {
      draw3DObject(this->object1);
    }
    else
    {
      draw3DObject(this->object2);
    }
}

void Circle::set_position(double x, double y,double z) {
    this->position = glm::vec3(x, y, z);
}
Compass::Compass(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->cplane_position = glm::vec3(0, 0, 0);
    this->speed = .2;
    this->rotation = 0;
    float pi = 3.14;
    static int n = 100;
    this->timer = 0;
    int i;
    GLfloat data[9*n+15];
    for(i=0;i<n;i++)
  {
  	data[9*i] = .9*cos(2*pi*i/n);
	data[9*i+1] =.9*sin(2*pi*i/n);
	data[9*i+2] = 0;  
	data[9*i+3] = .9*cos(2*pi*(i+1)/n);
	data[9*i+4] = .9*sin(2*pi*(i+1)/n);
	data[9*i+5] = 0;
	data[9*i+6] = 0;
	data[9*i+7] = 0;
	data[9*i+8] = 0;
  } 
   GLfloat _data[9*n+15];
    for(i=0;i<n;i++)
  {
   _data[9*i] = 0.8*cos(2*pi*i/n);
	_data[9*i+1] = 0.8*sin(2*pi*i/n);
	_data[9*i+2] = 0;
	_data[9*i+3] = 0.8*cos(2*pi*(i+1)/n);
	_data[9*i+4] = 0.8*sin(2*pi*(i+1)/n);
	_data[9*i+5] = 0;
	_data[9*i+6] = 0;
	_data[9*i+7] = 0;
	_data[9*i+8] = 0;

  }
  static const GLfloat buffer_data[] =  {
      .1,-.1,0,
      0,0,0,
      0,.1,0,
      0,0,0,
      -.1,-.1,0,
      0,.1,0,
  };
    this->base1 = create3DObject(GL_TRIANGLES, 3*n, _data,COLOR_Cyan, GL_FILL);
    this->base2 = create3DObject(GL_TRIANGLES, 3*n, data,COLOR_WHITE, GL_FILL);
    this->plane_pos = create3DObject(GL_TRIANGLES,6, buffer_data,COLOR_Grey, GL_FILL);
    
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base2);
    draw3DObject(this->base1);
    for(int i =0;i<5;i++)
    {
      //this->cpos[i].set_position(this->position.x+this->cpos[i].position.x,this->position.y+this->cpos[i].position.y,0);
      this->cpos[i].draw(VP);
    }
    glm::mat4 complane = glm::mat4(1.0f);
    translate = glm::translate (this->cplane_position + this->position); 
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f),glm::vec3(0,0,1));       // glTranslatef
     complane *=(translate*rotate);
    MVP = VP * complane;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->plane_pos);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick(){
  
}
