#include "dashboard.h"
#include "main.h"
using namespace std;
Dashboard::Dashboard(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->scale_factor_altitude = glm::vec3(.1,1,0);
    this->scale_factor_speed = glm::vec3(.1,1,0);
    this->scale_factor_fuel = glm::vec3(1,1,0);
    this->scale_factor_health = glm::vec3(1,1,0);
    static const GLfloat g_vertex_buffer_data[] = {
        -1,.3,0,
        -1,.8,0,
        1,.8,0,
        1,.8,0,                // Altitude
        1,.3,0,
        -1,.3,0,

        -1,-.3,0,
        -1,.2,0,
        1,.2,0,
        1,.2,0,                // Speed
        1,-.3,0,
        -1,-.3,0,

        -1,-.9,0,
        -1,-.4,0,
        1,-.4,0,
        1,-.4,0,                // fuel
        1,-.9,0,
        -1,-.9,0,

        -1.1,-.9,0,
        -1.4,-.9,0,
        -1.4,.8,0,             //Health
        -1.4,.8,0,
        -1.1,.8,0,
        -1.1,-.9,0,

        1,-1.1,0,
        -1.5,-1.1,0,
        -1.5,1.1,0,
        -1.5,1.1,0,
        1,1.1,0,
        1,-1.1,0,

    };
  this->altitude = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data,COLOR_RED, GL_FILL);
  this->speed = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data+6*3,COLOR_DGREEN, GL_FILL);
  this->fuel = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data+12*3,COLOR_GOLD, GL_FILL);
  this->health = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data+18*3,COLOR_YGREEN, GL_FILL);
  this->back = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data+24*3,COLOR_Grey, GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
     glm::mat4 back = glm::mat4(1.0f);
    glm::mat4 translat = glm::translate (this->position);    // glTranslatef
     back *=(translat);
    glm::mat4 MV = VP * back;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MV[0][0]);
    draw3DObject(this->back);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position+glm::vec3(-(1-this->scale_factor_altitude.x),0,0));    // glTranslatef
    glm::mat4 scale = glm::scale(Matrices.model,this->scale_factor_altitude);
    // glm::mat4 rotate = glm::rotate((float) (this->rotationy * M_PI / 180.0f),glm::vec3(0,1,0));
    // rotate *= glm::rotate((float) (this->rotationx * M_PI / 180.0f),glm::vec3(1,0,0));
    Matrices.model *= (translate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->altitude);

    Matrices.model2 = glm::mat4(1.0f);
     translate = glm::translate (this->position+glm::vec3(-(1-this->scale_factor_speed.x),0,0));    // glTranslatef
     scale = glm::scale(Matrices.model2,this->scale_factor_speed);
     Matrices.model2 *=(translate*scale);
    MVP = VP * Matrices.model2;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->speed);

    glm::mat4 fuelbar = glm::mat4(1.0f);
    translate = glm::translate (this->position+glm::vec3(-(1-this->scale_factor_fuel.x),0,0));    // glTranslatef
     scale = glm::scale(fuelbar,this->scale_factor_fuel);
     fuelbar *=(translate*scale);
    MVP = VP * fuelbar;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->fuel);

    glm::mat4 healthbar = glm::mat4(1.0f);
    translate = glm::translate (this->position+glm::vec3(0,-(1.7/2-1.7*this->scale_factor_health.y/2.0),0));    // glTranslatef
     scale = glm::scale(healthbar,this->scale_factor_health);
     healthbar *=(translate*scale);
    MVP = VP * healthbar;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->health);

     
}

void Dashboard::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Dashboard::tick(){
}
