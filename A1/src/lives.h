#include "main.h"

#ifndef LIVES_H
#define LIVES_H


class Lives {
public:
    Lives() {}
    Lives(float x, float y, color_t color, string textureFile);
    glm::vec3 position;
    float rotation;
    double speed;
    GLuint life_img;
    int R;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    
private:
    VAO *object;
};

#endif // EMPTY_H
