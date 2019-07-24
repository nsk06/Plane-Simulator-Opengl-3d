#include "sphere.h"
#include "main.h"

Sphere::Sphere(double x, double y, double z,float radius, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotationx = 0;
    this->rotationy = 0;
    this->speed = .3;
    this->yspeed =0;
    this->type = 0;
    this->timer  = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sphere has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[90000];
    int n = 100;
    double angle = (2*M_PI)/double(n);
    int j=0;
    for(j=0;j<n;j++) {
        int i = 0;
        for (i=0;i<n;i++) 
        {
            int k = n*i + j;
            vertex_buffer_data[9*k] = 0;
            vertex_buffer_data[9*k + 1] = 0;  
            vertex_buffer_data[9*k + 2] = radius*sin(j*angle);
            vertex_buffer_data[9*k + 3] = radius*cos(i*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 4] = radius*sin(i*angle)*cos(j*angle);
            vertex_buffer_data[9*k + 5] = radius*sin(j*angle); 
            vertex_buffer_data[9*k + 6] = radius*cos((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 7] = radius*sin((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 8] = radius*sin(j*angle); 
        }
    }
        this->object = create3DObject(GL_TRIANGLES, n*n*3, vertex_buffer_data, color, GL_FILL);

}

void Sphere::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of Sphere arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sphere::set_position(double x, double y,double z) {
    this->position = glm::vec3(x, y, z);
}

 void Sphere::tick() {
     if(this->type == 1)
    {   
        this->timer += 1.0/200.0;
        this->position.y -= this->timer;
        return;
    }
    this->yspeed = this->speed*cos(this->rotationx*M_PI/180.0f); 
    this->position.y += this->yspeed;
    if(this->type == 2)
    {
        this->position.z += this->speed*sin(this->rotationx*M_PI/180)*cos(this->rotationy*M_PI/180.0f); 
        this->position.x += this->speed*sin(this->rotationx*M_PI/180)*sin(this->rotationy*M_PI/180.0f);
        return;
    }
    this->yspeed -= 1.0/100.0;
    this->position.z += 2*this->speed*sin(this->rotationx*M_PI/180)*cos(this->rotationy*M_PI/180.0f); 
    this->position.x += 2*this->speed*sin(this->rotationx*M_PI/180)*sin(this->rotationy*M_PI/180.0f); 
    
    //return this->position.y < -5.0f.0;

}

// bounding_box_t Sphere::bounding_box() {
//     double x = this->position.x.0, y = this->position.y.0, z = this->position.z.0;
//     bounding_box_t bbox = { x.0, y.0,z.0, radi, this->radius, this->radius };
//     return bbox;
// }