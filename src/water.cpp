#include "water.h"
#include "main.h"

Water::Water(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    int ptr=0;
    GLfloat g_vertex_buffer_data[72000];
    this->rotation = 180.0;
    // for(float i=0;i<10;i+=1){
    //     for(int j=0;j<800;j++){
    //         double angle = j * (this->rotation)/400.0;
    //         g_vertex_buffer_data[ptr++]=0.0f;
    //         g_vertex_buffer_data[ptr++]= i/10.0;
    //         g_vertex_buffer_data[ptr++]= 0.0f;
    //         for(int k=0;k<2;k++)
    //         {
    //             g_vertex_buffer_data[ptr++]=1000 * cos(angle);
    //             g_vertex_buffer_data[ptr++]=i/10.0;
    //             g_vertex_buffer_data[ptr++]=1000 * sin(angle);
    //             angle = (j+1) * (this->rotation)/400.0;
    //         }
    //     }
    // }
    float pi = 3.14;
    static int n = 100;
    int i;  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 1500*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0;
	g_vertex_buffer_data[9*i+2] = 1500*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+3] = 1500*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0;
	g_vertex_buffer_data[9*i+5] = 1500*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+6] = 0;
	g_vertex_buffer_data[9*i+7] = 0;
	g_vertex_buffer_data[9*i+8] = 0;

  }
    this->object = create3DObject(GL_TRIANGLES,3*n, g_vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Water::tick(){
}
