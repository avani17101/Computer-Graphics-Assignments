#include "main.h"

#ifndef BATTERY_H
#define BATTERY_H


class Battery {
public:
    Battery() {}
    Battery(float x, float y, color_t color, string textureFile);
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
