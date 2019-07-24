#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->target_dir = glm::vec4(0,0,-8,1);
    this->rotation = 0;
    this->rotationy = 0;
    this->rotationz = 0;
    this->rotationx = 0;
    this->keypress = 0;
    this->timer =0;
    this->powertime =-1;
    this->score  = 0;
    this->axes_of_rotation = glm::vec3(0,0,1);
    speed = .3;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // static const GLfloat vertex_buffer_data[] = {
    static int n = 100;
    static int m = 4;
GLfloat g_vertex_buffer_data[9*n+15];
  int i;
  float pi = 3.14;
  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 0.4*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0.4*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 1.5f ;
	g_vertex_buffer_data[9*i+3] = 0.4*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0.4*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 1.5f;
	g_vertex_buffer_data[9*i+6] = 0.4*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+7] = 0.4*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+8] = -1.5f;

  }
    GLfloat vertex_buffer_data[9*n+15];
    for(i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = 0.4*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = 0.4*sin(2*pi*i/n);
	vertex_buffer_data[9*i+2] = -1.5f ;
	vertex_buffer_data[9*i+3] = 0.4*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] = 0.4*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+5] = -1.5f;
	vertex_buffer_data[9*i+6] = 0.4*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+7] = 0.4*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+8] = 1.5f;

  }
   GLfloat _data[9*n+15];
    for(i=0;i<n;i++)
  {
  _data[9*i] = 0.4*cos(2*pi*i/n);
	_data[9*i+1] = 0.4*sin(2*pi*i/n);
	_data[9*i+2] = -1.5f ;
	_data[9*i+3] = 0.4*cos(2*pi*(i+1)/n);
	_data[9*i+4] = 0.4*sin(2*pi*(i+1)/n);
	_data[9*i+5] = -1.5f;
	_data[9*i+6] = 0;
	_data[9*i+7] = 0;
	_data[9*i+8] = -3;

  }
  GLfloat _ata[9*m+15];
    for(i=0;i<m;i++)
  {
  _ata[9*i] = 0.45*cos(2*pi*i/m);
	_ata[9*i+1] = 0.45*sin(2*pi*i/m);
	_ata[9*i+2] = -8 ;
	_ata[9*i+3] = 0.45*cos(2*pi*(i+1)/m);
	_ata[9*i+4] = 0.45*sin(2*pi*(i+1)/m);
	_ata[9*i+5] = -8;
	_ata[9*i+6] = 0;
	_ata[9*i+7] = 0;
	_ata[9*i+8] = -8;

  }
   GLfloat data[9*n+15];
    for(i=0;i<n;i++)
  {
  	data[9*i] = 0.3*cos(2*pi*i/n);
	data[9*i+1] = 0.3*sin(2*pi*i/n);
	data[9*i+2] = 1.5;  
	data[9*i+3] = 0.3*cos(2*pi*(i+1)/n);
	data[9*i+4] = 0.3*sin(2*pi*(i+1)/n);
	data[9*i+5] = 1.5;
	data[9*i+6] = 0;
	data[9*i+7] = 0;
	data[9*i+8] = 1.5;

  }
    static const GLfloat buffer_data[] =  {
            0.4,0,1.4,
            1.5f,0,1.4f,
            1.5f,0,1.2,
            1.5f,0,1.2,
            0.4f,0,1.2,
            0.4,0,1.4f,

            -0.4,0,1.4f,
            -1.5f,0,1.4f,
            -1.5f,0,1.2,
            -1.5f,0,1.2,
            -0.4f,0,1.2,
            -0.4,0,1.4f,

            0.4,0,1.2,
            1.5,0,1.2,
            0.4,0,0.9,

            -0.4,0,1.2,
            -1.5,0,1.2,
            -0.4,0,0.9,
//////////////////////////////////////////////////////////////////////////////////////////////////
            0.4,0,-0.8,
            2.5f,0,-.8f,
            2.5f,0,-1,
            2.5f,0,-1,
            0.4f,0,-1,
            0.4,0,-.8f,

            -0.4,0,-.8f,
            -2.5f,0,-.8f,
            -2.5f,0,-1,
            -2.5f,0,-1,
            -0.4f,0,-1,
            -0.4,0,-.8f,

            0.4,0,-1,
            2.5,0,-1,
            0.4,0,-1.4,

            -0.4,0,-1,
            -2.5,0,-1,
            -0.4,0,-1.4,

////////////////////////////////////////////////////////////////////////////////////////////////////
            0,.4,-.3,
            0,.4,.5,
            0,2,.5,

            .01,.4,.5,
            .01,2,.5,
            -.01,2,.5,
            -.01,2,.5,
            -.01,.4,.5,
            .01,.4,.5,

///////////////////////////////////////////////////////////////////////////////////////////////////
            .3,.4,1.5,
            0,1,1.5,
            -.3,.4,1.5,
    };
    this->mid1 = create3DObject(GL_TRIANGLES, 3*n, g_vertex_buffer_data,COLOR_BLACK, GL_FILL);
    this->mid2 = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data,COLOR_Grey, GL_FILL);
    this->back = create3DObject(GL_TRIANGLES, 36, buffer_data,COLOR_Silver, GL_FILL);
    this->flag = create3DObject(GL_TRIANGLES, 9, buffer_data+36*3,COLOR_RED, GL_FILL);
    this->front = create3DObject(GL_TRIANGLES, 3*n, _data,COLOR_Met, GL_FILL);
    this->fire = create3DObject(GL_TRIANGLES, 3*n, data,COLOR_ORANGE, GL_FILL);
    this->target = create3DObject(GL_TRIANGLES, 3*m, _ata,COLOR_WHITE, GL_LINE);
    this->power = create3DObject(GL_TRIANGLES, 3, buffer_data+45*3,COLOR_FIRE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotationy * M_PI / 180.0f),glm::vec3(0,1,0));
    rotate *= glm::rotate((float) (this->rotationx * M_PI / 180.0f),glm::vec3(1,0,0));
    rotate *= glm::rotate((float) (this->rotationz * M_PI / 180.0f),glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    this->target_dir = rotate*(glm::vec4(0,0,-8,1));
    // std::cout << this->target_dir.x  << "yo" << this->target_dir.y  << "hey"<<this->target_dir.z << std::endl;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->mid1);
    draw3DObject(this->mid2);
    draw3DObject(this->back);
    draw3DObject(this->flag);    
    draw3DObject(this->front);
    draw3DObject(this->fire);
    draw3DObject(this->target);
    if(this->powertime > 0)
    {
    draw3DObject(this->power);      
    }
}

void Plane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
  if(this->powertime >=0)
  {
    this->powertime++;
    if(this->powertime > 300)
    {
      this->powertime = -1;
    }
  }
    if(this->rotationx == 360)
    {
        this->rotationx = 0;
    }
     if(this->rotationy == 360)
    {
        this->rotationy = 0;
    } if(this->rotationz == 360)
    {
        this->rotationz = 0;
    }
     if(this->keypress == 0)
    {
      if(this->speed > .3)
      {
        this->speed -= .005;
      }
        this->timer = 0;
    }
    else 
    {
      this->timer += 1.0/60.0;
      if(this->speed < 2)
      {
        this->speed += .005*this->timer;
      }
    }
}

