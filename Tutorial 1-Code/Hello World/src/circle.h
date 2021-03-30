#include "main.h"

#ifndef CIRCLE_H
#define CIRCLE_H


class Circle {
public:
    Circle() {}
    Circle(float x, float y, color_t color);
    glm::vec3 position;
    bounding_box_t bounding_box;
    bounding_box_t return_bounding_box ();
    float rotation;
    void draw(glm::mat4 VP);
    float ballx();
    float bally();
    void set_position(float x, float y);
    void tick();
    void move(float x,float y);
    double speed;
private:
    VAO *object;
};

#endif // CIRCLE_H
