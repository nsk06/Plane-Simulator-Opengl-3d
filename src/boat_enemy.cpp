#include "boat_enemy.h"
#include "main.h"


Boat_Enemy::Boat_Enemy(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->speed = .01;
    this->rotation = 0;
    this->timer = 0;
    this->type = 0;
    this->start_fire = false;
    this->structure[0] = Cuboid(this->position.x,this->position.y,this->position.z,2,1,4.5,COLOR_Sienaa);
    this->structure[1] = Cuboid(this->position.x+1,this->position.y,this->position.z,.2,4,4,COLOR_ORANGE);
    this->structure[2] = Cuboid(this->position.x-1,this->position.y,this->position.z,.2,4,4,COLOR_ORANGE);
    this->structure[1].rotation = -30;
    this->structure[2].rotation = 30;
    GLfloat g_vertex_buffer_data[] = {
        -2,   1,-2,
        -1, -1, -2,
        0, 2,-4,

        2, 1,-2,
        1,  -1,-2,
        0, 2,-4,

        0, 2,-4,
        -1, -1,-2,
        1, -1,-2,

        -2, 1, 2,
        -1,-1, 2,
        0, 2, 4,

        2, 1,2,
        1,  -1,2,
        0,  2,4,

        0, 2,4,
        -1,-1, 2,
        1,-1, 2,

    };
    this->front = create3DObject(GL_TRIANGLES, 6 * 3, g_vertex_buffer_data,COLOR_Yell);
    this->Cannon = Cylinder(this->position.x,this->position.y,this->position.z,.4,5,COLOR_PURE);
    this->Cannon2 = Cylinder(this->position.x,this->position.y,this->position.z,.4,5,COLOR_WHITE);
}

void Boat_Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
     if(cam_view != 5)
    {
      MVP *= (glm::scale(glm::vec3(exp(camera_zoom))));
    }
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->front);
    this->structure[0].draw(VP);
    this->structure[1].draw(VP);
    this->structure[2].draw(VP);
    if(this->type == 1)
    {
        this->Cannon.draw(VP);
    }
    else
    {
        this->Cannon2.draw(VP);
    }
     if(this->cannonballs.size() > 0)
        {
            std::vector<Sphere>::iterator it;
            for(auto it = this->cannonballs.begin();it!=this->cannonballs.end();it++)
            {
                (*it).draw(VP);
            }
        }
}

void Boat_Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat_Enemy::tick() {
    this->timer++;
    this->position.z -= this->speed;
    if(this->type == 1)
    {
        this->Cannon.set_position(this->position.x,this->position.y,this->position.z);
    }
    else
    {
        this->Cannon2.set_position(this->position.x,this->position.y,this->position.z);
    }
    for(int i=0;i<3;i++)
    {
        this->structure[i].position.z -= this->speed;
    }
    if(this->type == 1)
    {
        if(this->timer%60 == 0 && this->start_fire == true)
        {
                Sphere s = Sphere(this->Cannon.position.x+5*sin(this->Cannon.rotationx*M_PI/180)*sin(this->Cannon.rotationy*M_PI/180),
                    this->Cannon.position.y+5*cos(this->Cannon.rotationx*M_PI/180),
                    this->Cannon.position.z/*+1*sin(this->Cannon.rotationx*M_PI/180)*cos(this->Cannon.rotationy*M_PI/180)*/,.2,COLOR_FIRE);
                s.rotationx = this->Cannon.rotationx;
                s.rotationy = this->Cannon.rotationy;
                s.type = 2;
                this->cannonballs.push_back(s);            
        }
    }
}


