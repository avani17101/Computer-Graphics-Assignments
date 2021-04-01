#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color, string ImgFile);
    glm::vec3 position;
    double speed;
    GLuint Img;
    GLuint Img_right;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float rotation;
    int direction;
  
    
private:
    VAO *object;
};

#endif // EMPTY_H
