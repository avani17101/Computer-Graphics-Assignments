#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // this->bounding_box = { this->position.x, this->position.y, 3, 3 };
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -8.0f,-8.0f,-2.0f,
        -8.0f,152.0f,-2.0f,
        152.0f,152.0f,-2.0f,
        152.0f,-8.0f,-2.0f,
        152.0f,152.0f,-2.0f,
        -8.0f,-8.0f,-2.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    // this->bounding_box = { this->position.x, this->position.y, 2, 2 };
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


// float Plane::planex()
// {
    
//     return this->position.x;
// }

bounding_box_t Plane :: return_bounding_box () {
    return this->bounding_box;
}

// float Plane::planey()
// {
//     return this->position.y;
// }
void Plane::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

