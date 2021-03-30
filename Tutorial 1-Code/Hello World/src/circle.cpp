#include "circle.h"
#include "main.h"
// #include "Vertex"


void CreateCircleArray(GLfloat circle2[60],float radius, float x, float y, int fragments)
{
     const float PI = 3.1415926f;


     float increment = 2.0f * PI / fragments;
        int i=0;
     for (float currAngle = 0.0f; currAngle <= 2.0f * PI; currAngle += increment)
     {
         circle2[i++]=radius * cos(currAngle) + x;
         circle2[i++]= radius * sin(currAngle) + y;
         circle2[i++]= -1.0f;
     }


}
Circle::Circle(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->bounding_box = { this->position.x, this->position.y, 3, 3 };
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[60];
    CreateCircleArray(vertex_buffer_data,8,0,0,20);

    this->object = create3DObject(GL_LINE_LOOP, 60, vertex_buffer_data, color, GL_FILL);
}

void Circle::draw(glm::mat4 VP) {
    this->bounding_box = { this->position.x, this->position.y, 2, 2 };
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

void Circle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
void Circle::move(float x,float y){
    this->position.x+=x;
    this->position.y+=y;

}


// float Circle::circlex()
// {
    
//     return this->position.x;
// }

// bounding_box_t Circle :: return_bounding_box () {
//     return this->bounding_box;
// }

// float Circle::circley()
// {
//     return this->position.y;
// }
void Circle::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

