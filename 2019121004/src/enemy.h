#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color, string ImgFile);
    glm::vec3 position;
    GLuint Img;
    GLuint Img_right;
    float rotation;
    double speed;
    
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    
    int direction;
private:
    VAO *object;
};

#endif // EMPTY_H
