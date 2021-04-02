#include "main.h"

#ifndef FIRE_H
#define FIRE_H


class Fire {
public:
    Fire() {}
    Fire(float x, float y, color_t color, string textureFile);
    glm::vec3 position;
    GLuint Texture[3];
    int count, curr, images;
    double speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float rotation;
    
private:
    VAO *object;
};

#endif // EMPTY_H
