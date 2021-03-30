#include "hwall.h"
#include "main.h"
#define GLM_ENABLE_EXPERIMENTAL
Hwall::Hwall(float x1, float y1,  color_t color) {
    x1*=8;
    y1*=8;
    this->position = glm::vec3(x1, y1, 0);
    this->bounding_box = { this->position.x, this->position.y, 4, 1 };
    // this->rotation = 0;

    speed = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
            x1,y1+7.5f,-1.0f,
            x1,y1+8.5f,-1.0f,
            x1+8.0f,y1+7.5f,-1.0f,

            x1,y1+8.5f,-1.0f,
            x1+8.0f,y1+7.5f,-1.0f,
            x1+8.0f,y1+8.5f,-1.0f


        };
    // triangle (vertex_buffer_data[0],vertex_buffer_data[1],vertex_buffer_data[2]);


    // cross(glm::vec3(vertex_buffer_data[0],vertex_buffer_data[1],vertex_buffer_data[2]), glm::vec3(vertex_buffer_data[3],vertex_buffer_data[4],vertex_buffer_data[5]))[0]

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Hwall::draw(glm::mat4 VP) {
    this->bounding_box = { this->position.x, this->position.y, 4, 1 };
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

void Hwall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Hwall :: return_bounding_box () {
    return this->bounding_box;
}

void Hwall::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
void Hwall::move(float x,float y){
    this->position.x += x;
    this->position.y+= y;
}

float Hwall::getx(){
    return this->position.x;
}

float Hwall::gety(){
    return this->position.y;
}