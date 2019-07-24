#include "cone.h"
#include "main.h"
Cone::Cone(float x, float y,float z, float radius , float height,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rot_dir = true;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Cone has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     float pi = 3.14;
    static int n = 100;
    int i;
    GLfloat vertex_buffer_data[9*n+15];
    for(i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = radius*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = 0;
	vertex_buffer_data[9*i+2] = radius*sin(2*pi*i/n);
	vertex_buffer_data[9*i+3] = radius*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] = 0;
	vertex_buffer_data[9*i+5] = radius*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+6] = 0;
	vertex_buffer_data[9*i+7] = height;
	vertex_buffer_data[9*i+8] = 0;

  }
    this->object = create3DObject(GL_TRIANGLES,3*n, vertex_buffer_data, color, GL_FILL);
}

void Cone::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1,0,0));
    // No need as coords centered at 0, 0, 0 of Cone arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    }

void Cone::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cone::tick() {
}
