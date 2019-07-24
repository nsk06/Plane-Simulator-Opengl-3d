#include "island.h"
#include "main.h"
using namespace std;
Island::Island(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->start_fire = false;
    int ptr=0;
    float pi = 3.14;
    static int n = 100;
    this->lives = 3;
    this->timer = 0;
    this->type = 0;
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
  this->rocks[0] = Cuboid(this->position.x-2,this->position.y,this->position.z,1.5,1,2,COLOR_Grey);
  this->rocks[1] = Cuboid(this->position.x+2,this->position.y,this->position.z,1.5,1,2,COLOR_Grey);
  this->cannons[0] = Cylinder(this->rocks[0].position.x,this->rocks[0].position.y+1,this->rocks[0].position.z,.4,5,COLOR_BACKGROUND);
  this->cannons[1] = Cylinder(this->rocks[1].position.x,this->rocks[1].position.y+ 1,this->rocks[0].position.z,.4,5,COLOR_BACKGROUND);
  this->cannons[0].rotationx = -45;
  this->cannons[1].rotationx = 45;
  this->objects[0] = Cone(this->position.x,this->position.y,this->position.z+6,2,3,COLOR_DGREEN);
  this->objects[1] = Cone(this->position.x,this->position.y,this->position.z-6,2,3,COLOR_DGREEN);
  this->objects[2] = Cone(this->position.x-6,this->position.y,this->position.z,2,3,COLOR_DGREEN);
  this->objects[3] = Cone(this->position.x+6,this->position.y,this->position.z,2,3,COLOR_DGREEN);
 
this->base = create3DObject(GL_TRIANGLES,3*n, g_vertex_buffer_data, color, GL_FILL);
this->base2 = create3DObject(GL_TRIANGLES,3*n, g_vertex_buffer_data,COLOR_Maroon, GL_FILL); 
}

void Island::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    Matrices.model *=  glm::translate(position);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->type == 1)
    {
        draw3DObject(this->base);
         for(int i=0;i<4;i++)
        {
            this->objects[i].draw(VP);
        }
        return;
    }
    if(this->lives > 0)
    {
        draw3DObject(this->base);
            for(int i=0;i<2;i++)
        {
            this->rocks[i].draw(VP);
        }
        for(int i=0;i<2;i++)
        {
            this->cannons[i].draw(VP);
        }
        for(int i=0;i<4;i++)
        {
            this->objects[i].draw(VP);
        }
        if(this->fireballs.size() > 0)
        {
            std::vector<Sphere>::iterator it;
            for(auto it = this->fireballs.begin();it!=this->fireballs.end();it++)
            {
                (*it).draw(VP);
            }
        }
    }
    else
    {
        draw3DObject(this->base2);

    }
    
}

void Island::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Island::tick(){
    if(this->lives > 0)
    {
        for(int i=0;i<2;i++)
        {
                this->cannons[i].rotationy += 1;
            
        }
        this->timer++;
        if(this->timer%50 == 0 && this->start_fire == true)
        {
            for(int i=0;i<2;i++)
            {
                Sphere s = Sphere(this->cannons[i].position.x-5*sin(this->cannons[i].rotationx*M_PI/180)*sin(this->cannons[i].rotationy*M_PI/180),
                    this->cannons[i].position.y+5*cos(this->cannons[i].rotationx*M_PI/180),
                    this->cannons[i].position.z+5*sin(this->cannons[i].rotationx*M_PI/180)*cos(this->cannons[i].rotationy*M_PI/180),.2,COLOR_FIRE);
                s.rotationx = this->cannons[i].rotationx;
                s.rotationy = this->cannons[i].rotationy;
                this->fireballs.push_back(s);            
            }
        }
    }
}
