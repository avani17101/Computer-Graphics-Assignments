#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, color_t color, string ImgFile) {
    this->position = glm::vec3(x, y, 0);
    speed = 1;
    this->Img = loadBMP_custom("assets/enemy.bmp");
    this->Img_right = loadBMP_custom("assets/enemy_right.bmp");
    
    this->rotation = 0;
    this->direction = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        0.0f, -0.0f, 0.0f,
        1.0f, -0.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, -0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    static const GLfloat uv_buffer_data[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, -0.0f,
        0.0f, 1.0f,
        0.0f, -0.0f,
        1.0f, -0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, uv_buffer_data, color, GL_FILL, "assets/player.bmp");
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    if(this->direction == 90)
        drawPlayer(this->object, this->Img_right);
    else 
        drawPlayer(this->object, this->Img);

}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

