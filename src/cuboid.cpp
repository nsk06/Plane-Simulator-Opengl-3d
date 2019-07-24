#include "cuboid.h"
#include "main.h"
Cuboid::Cuboid(float x, float y,float z, float width , float height , float depth,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->dimensions  = glm::vec3(width, height , depth);
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Cuboid has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -width/2 ,-height/2 ,-depth/2, 
        -width/2 ,-height/2 , depth/2,
        -width/2 , height/2 , depth/2, 

        width/2 , height/2 ,-depth/2, 
        -width/2 ,-height/2 ,-depth/2,
        -width/2 , height/2 ,-depth/2, 

        width/2 ,-height/2 , depth/2,
        -width/2 ,-height/2 ,-depth/2,
        width/2 ,-height/2 ,-depth/2,

        width/2 , height/2 ,-depth/2,
        width/2 ,-height/2 ,-depth/2,
        -width/2 ,-height/2 ,-depth/2,

        -width/2 ,-height/2 ,-depth/2,
        -width/2 , height/2 , depth/2,
        -width/2 , height/2 ,-depth/2,

        width/2 ,-height/2 , depth/2,
        -width/2 ,-height/2 , depth/2,
        -width/2 ,-height/2 ,-depth/2,

        -width/2 , height/2 , depth/2,
        -width/2 ,-height/2 , depth/2,
        width/2 ,-height/2 , depth/2,

        width/2 , height/2 , depth/2,
        width/2 ,-height/2 ,-depth/2,
        width/2 , height/2 ,-depth/2,

        width/2 ,-height/2 ,-depth/2,
        width/2 , height/2 , depth/2,
        width/2 ,-height/2 , depth/2,

        width/2 , height/2 , depth/2,
        width/2 , height/2 ,-depth/2,
        -width/2 , height/2 ,-depth/2,

        width/2 , height/2 , depth/2,
        -width/2 , height/2 ,-depth/2,
        -width/2 , height/2 , depth/2,

        width/2 , height/2 , depth/2,
        -width/2 , height/2 , depth/2,
        width/2 ,-height/2 , depth/2
    };


    this->object = create3DObject(GL_TRIANGLES,36, vertex_buffer_data, color, GL_FILL);
}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of Cuboid arouund which we waant to rotate
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

void Cuboid::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cuboid::tick() {
}

// bounding_box_t Cuboid::bounding_box() {
//     float x = this->position.x, y = this->position.y, z = this->position.z;
//     float width = this->dimensions.x, height = this->dimensions.y, depth = this->dimensions.z;
//     bounding_box_t bbox = { x, y,z, width, height, depth };
//     return bbox;
// }
