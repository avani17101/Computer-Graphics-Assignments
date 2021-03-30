#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
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
