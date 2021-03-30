#include "main.h"

#ifndef VWALL_H
#define VWALL_H
#define GLM_ENABLE_EXPERIMENTAL

class Vwall {
public:
    Vwall() {}
    Vwall(float x1, float y1, color_t color);
    glm::vec3 position;
    float rotation;
    bounding_box_t bounding_box;
    bounding_box_t return_bounding_box ();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move(float x, float y);
    float getx();
    float gety();
    double speed;
private:
    VAO *object;
};

#endif // VWALL_H