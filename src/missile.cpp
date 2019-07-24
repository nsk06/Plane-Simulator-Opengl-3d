#include "missile.h"
#include "main.h"
using namespace std;
Missile::Missile(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    int ptr=0;
    this->rotation = 0;
    this->rotationx = 0;
    this->rotationy = 0;
    this->speed = .6;
    this->yspeed = .1;
    this->type = 0;
    float pi = 3.14;
    static int n = 100;
    this->timer = 0;
    GLfloat g_vertex_buffer_data[1000];
    int i;  

  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 0.25*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0.25*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = .5f ;
	g_vertex_buffer_data[9*i+3] = 0.25*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0.25*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = .5f;
	g_vertex_buffer_data[9*i+6] = 0.25*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+7] = 0.25*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+8] = -.5f;

  }
    GLfloat vertex_buffer_data[9*n+15];
    for(i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = 0.25*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = 0.25*sin(2*pi*i/n);
	vertex_buffer_data[9*i+2] = -.5f ;
	vertex_buffer_data[9*i+3] = 0.25*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] = 0.25*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+5] = -.5f;
	vertex_buffer_data[9*i+6] = 0.25*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+7] = 0.25*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+8] = .5f;

  }
   GLfloat _data[9*n+15];
    for(i=0;i<n;i++)
  {
  	_data[9*i] = 0.25*cos(2*pi*i/n);
	_data[9*i+1] = 0.25*sin(2*pi*i/n);
	_data[9*i+2] = -.5f ;
	_data[9*i+3] = 0.25*cos(2*pi*(i+1)/n);
	_data[9*i+4] = 0.25*sin(2*pi*(i+1)/n);
	_data[9*i+5] = -.5f;
	_data[9*i+6] = 0;
	_data[9*i+7] = 0;
	_data[9*i+8] = -1.5;

  }
  GLfloat data[9*n+15];
    for(i=0;i<n;i++)
  {
  	data[9*i] = 0.25*cos(2*pi*i/n);
	data[9*i+1] = 0.25*sin(2*pi*i/n);
	data[9*i+2] = -.5f ;
	data[9*i+3] = 0.25*cos(2*pi*(i+1)/n);
	data[9*i+4] = 0.25*sin(2*pi*(i+1)/n);
	data[9*i+5] = -.5f;
	data[9*i+6] = 0;
	data[9*i+7] = 0;
	data[9*i+8] = -.5;

  }
  this->base1 = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data,COLOR_BACKGROUND, GL_FILL);
  this->base2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data,COLOR_Grey, GL_FILL);
  this->top = create3DObject(GL_TRIANGLES, 3*n, _data,COLOR_ORANGE, GL_FILL);
  this->back = create3DObject(GL_TRIANGLES, 3*n, data,COLOR_PURE, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotationy * M_PI / 180.0f),glm::vec3(0,1,0));
    rotate *= glm::rotate((float) (this->rotationx * M_PI / 180.0f),glm::vec3(1,0,0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base1);
    draw3DObject(this->base2);
    draw3DObject(this->top);
    if(this->type == 0)
    draw3DObject(this->back);
}

void Missile::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick(){
    this->timer += 1.0/60.0;
    if(this->type == 0)
    {
    this->position.y -= this->timer*this->yspeed;
    
    }
    if(this->type == 1)
    {
      
    }
    this->position.z -= this->speed*cos(this->rotationx*M_PI/180.0)*cos(this->rotationy*M_PI/180.0);
    this->position.x -= this->speed*cos(this->rotationx*M_PI/180.0)*sin(this->rotationy*M_PI/180.0);
    this->position.y += this->speed*sin(this->rotationx*M_PI/180.0);
}
