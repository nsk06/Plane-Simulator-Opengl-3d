#include "parachute.h"
#include "main.h"
using namespace std;
Parachute::Parachute(double x, double y, double z) {
    this->position = glm::vec3(x, y, z);
    this->type = 0;
    this->rotation = 15;
    this->timer = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Parachute has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[1000];
    int n = 100;
    double pi = 3.14;
    int i=0;  
     for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 2*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 2*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 1 ;
	g_vertex_buffer_data[9*i+3] = 2*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 2*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 1;
	g_vertex_buffer_data[9*i+6] = 2*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+7] = 2*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+8] = -1;

  }
    GLfloat vertex_buffer_data[9*n+15];
    for(i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = 2*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = 2*sin(2*pi*i/n);
	vertex_buffer_data[9*i+2] = -1 ;
	vertex_buffer_data[9*i+3] = 2*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] =2*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+5] = -1;
	vertex_buffer_data[9*i+6] = 2*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+7] = 2*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+8] = 1;

  }
     static const GLfloat _buffer_data[] = {
        0.5f,0.0f,0.0f,
        -0.2f,0.0f,0.0f,
        -0.2f,.5f,0.0f,       //Face
        -0.2f,.5f,0.0f,
        0.5f,.5f,0.0f,
        0.5f,0.0f,0.0f,

        
        .5f,.0f,0.0f,
        .5f,-.5f,0.0f,
        -.2f,-.5f,0.0f,      //Legs
        -.2f,-.5f,0.0f,
        -.2f,.0f,0.0f,
        .5f,.0f,0.0f,

        .5f,-.5f,0.0f,
        .5f,-.7f,0.0f,
        -.2f,-.7f,0.0f,
        -.2f,-.7f,0.0f,      //shoes
        -.2f,-.5f,0.0f,
        .5f,-.5f,0.0f,
        .6f,-.7f,0.0f,
        .5f,-.7f,0.0f,     
        .5f,-.5f,0.0f,
          
    };
    static const GLfloat buffer_data[] ={
        .5f,.5f,0.0f,
        -.2f,.5f,0.0f,
        -.2f,.3f,0.0f,      //Hair
        -.2f,.3f,0.0f,
        .5f,.3f,0.0f,
        .5f,.5f,0.0f,

        -.2f,.5f,0.0f,
        -.2f,.0f,0.0f,
        -.3f,.0f,0.0f,      //Back
        -.3f,.0f,0.0f,
        -.3f,.5f,0.0f,
        -.2f,.5f,0.0f,
        
    };
    static const GLfloat _data[] ={ 
        .06,.5,0,
        -.06,.5,0,
        -.06,2,0,
        -.06,2,0,
        .06,2,0,
        .06,.5,0,

        .5,.5,0,
        .6,.4,0,
        1.4,1.6,0,
        1.4,1.6,0,
        1.3,1.5,0,
        .5,.5,0,

        -.3,.5,0,
        -.4,.4,0,
        -1.4,1.6,0,
        -1.4,1.6,0,
        -1.3,1.5,0,
        -.3,.5,0,
    };
    static const GLfloat _ata[] ={
        .25,-.5,1,
        -.25,-.5,1,
        -.25,.5,1,
        -.25,.5,1,       //health
        .25,.5,1,
        .25,-.5,1,

        .6,-.2,1,
        -.6,-.2,1,
        -.6,.2,1,
        -.6,.2,1,        //health
        .6,.2,1,
        .6,-.2,1,


        1.1-1,0+.3,1,
        .9-1,0+.3,1,
        .9-1,.5+.3,1,    //Sword up
        .9-1,.5+.3,1,
        1.1-1,.5+.3,1,
        1.1-1,0+.3,1,

        1.3-1,0+.3,1,
        .7-1,0+.3,1,
        .7-1,.1+.3,1,
        .7-1,.1+.3,1,    //Sword side
        1.3-1,.1+.3,1,
        1.3-1,0+.3,1,


        1.15-1,-.8+.3,1,
        .85-1,-.8+.3,1,
        .85-1,0+.3,1,
        .85-1,0+.3,1,     //Main sword
        1.15-1,0+.3,1,
        1.15-1,-.8+.3,1,

        1.15-1,-.8+.3,1,
        1-1,-1+.3,1,         //tip sword
        .85-1,-.8+.3,1,
    }; 

    this->object = create3DObject(GL_TRIANGLES, 1.2*n, g_vertex_buffer_data,COLOR_OLIVE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1.2*n, vertex_buffer_data,COLOR_OLIVE, GL_FILL);
    this->face = create3DObject(GL_TRIANGLES,6, _buffer_data, COLOR_Peach, GL_FILL);
    this->legs = create3DObject(GL_TRIANGLES,6, _buffer_data+6*3, COLOR_RED, GL_FILL);
    this->shoes = create3DObject(GL_TRIANGLES,9, _buffer_data+6*6, COLOR_YGREEN, GL_FILL);
    this->head = create3DObject(GL_TRIANGLES,12,buffer_data,COLOR_BLACK,GL_FILL);
    this->rop = create3DObject(GL_TRIANGLES,18,_data,COLOR_WHITE,GL_FILL);
    this->goodies[0] = Cuboid(this->position.x,this->position.y-1,this->position.z,1.5,1.5,2,COLOR_WHITE);
    this->goodies[1] = Cuboid(this->position.x,this->position.y-1,this->position.z,1.5,1.5,2,COLOR_Yell);
    this->health = create3DObject(GL_TRIANGLES,12,_ata,COLOR_RED,GL_FILL);
    this->swordA = create3DObject(GL_TRIANGLES,12, _ata+12*3, COLOR_PURE, GL_FILL);
    this->swordB = create3DObject(GL_TRIANGLES,9, _ata+24*3, COLOR_Met, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0, 1));
    // No need as coords centered at 0, 0, 0 of Parachute arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->rop);
if(this->type == 0)
{
    draw3DObject(this->face);
    draw3DObject(this->legs);
    draw3DObject(this->shoes);
    draw3DObject(this->head);
}
else if(this->type == 1)
{
    this->goodies[0].draw(VP);
    draw3DObject(this->health);
}
else if(this->type == 2)
{
    this->goodies[1].draw(VP);
    draw3DObject(this->swordA);
    draw3DObject(this->swordB);
}
}

void Parachute::set_position(double x, double y,double z) {
    this->position = glm::vec3(x, y, z);
}
void Parachute::tick()
{
    this->timer++;
   this->position.y -= 0.008*this->timer/200.0;
   if(this->type == 1)
   {
       this->goodies[0].set_position(this->position.x,this->position.y,this->position.z);
   }
   else if(this->type == 2)
   {
       this->goodies[1].set_position(this->position.x,this->position.y,this->position.z);

   }
}