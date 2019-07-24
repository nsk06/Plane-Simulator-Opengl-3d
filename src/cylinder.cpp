#include "cylinder.h"
#include "main.h"
Cylinder::Cylinder(float x, float y,float z, float radius , float height,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->rotationy = 0;
    this->rotationx = 0;
    this->rotationz = 0;
    this->rot_dir = true;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Cylinder has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     float pi = 3.14;
    static int n = 100;
    int i;
    GLfloat _buffer_data[9*n+15];
  for(i=0;i<n;i++)
  {
  	_buffer_data[9*i] = radius*cos(2*pi*i/n);
	_buffer_data[9*i+1] = 0;
	_buffer_data[9*i+2] = radius*sin(2*pi*i/n) ;
	_buffer_data[9*i+3] = radius*cos(2*pi*(i+1)/n);
	_buffer_data[9*i+4] = 0;
	_buffer_data[9*i+5] = radius*sin(2*pi*(i+1)/n);
	_buffer_data[9*i+6] = radius*cos(2*pi*i/n);
	_buffer_data[9*i+7] = height;
	_buffer_data[9*i+8] = radius*sin(2*pi*i/n);

  }
    GLfloat vertex_buffer_data[9*n+15];
    for(i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = radius*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = height;
	vertex_buffer_data[9*i+2] = radius*sin(2*pi*i/n);
	vertex_buffer_data[9*i+3] = radius*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] = height;
	vertex_buffer_data[9*i+5] = radius*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+6] = radius*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+7] = 0;
	vertex_buffer_data[9*i+8] = radius*sin(2*pi*(i+1)/n);

  }
    this->object1 = create3DObject(GL_TRIANGLES,3*n, vertex_buffer_data, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES,3*n, _buffer_data, color, GL_FILL);
}

void Cylinder::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotationy * M_PI / 180.0f), glm::vec3(0,1,0));
   rotate    *= glm::rotate((float) (this->rotationx * M_PI / 180.0f), glm::vec3(1,0,0));
   rotate    *= glm::rotate((float) (this->rotationz * M_PI / 180.0f), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of Cylinder arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Cylinder::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cylinder::tick() {
}
