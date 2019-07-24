#include "volcanoe.h"
#include "main.h"
using namespace std;
Volcanoe::Volcanoe(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    int ptr=0;
    float pi = 3.14;
    static int n = 100;
    this->timer = 0;
    GLfloat g_vertex_buffer_data[1000];
    int i;  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 8*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0;
	g_vertex_buffer_data[9*i+2] = 8*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+3] = 8*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0;
	g_vertex_buffer_data[9*i+5] = 8*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+6] = 0;
	g_vertex_buffer_data[9*i+7] = 0;
	g_vertex_buffer_data[9*i+8] = 0;

  }
  this->mount = Cone(this->position.x,this->position.y,this->position.z,5,7,COLOR_RED);
  this->base = create3DObject(GL_TRIANGLES,3*n, g_vertex_buffer_data, color, GL_FILL);
}

void Volcanoe::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->base);
    this->mount.draw(VP);
}

void Volcanoe::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcanoe::tick(){
}
