#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, color_t color);
    glm::vec3 position;
    bounding_box_t bounding_box;
    bounding_box_t return_bounding_box ();
    float rotation;
    void draw(glm::mat4 VP);
    float ballx();
    float bally();
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
