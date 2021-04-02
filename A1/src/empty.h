#include "main.h"

#ifndef EMPTY_H
#define EMPTY_H


class Empty {
public:
    Empty() {}
    Empty(float x, float y, color_t color, string textureFile);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // EMPTY_H
