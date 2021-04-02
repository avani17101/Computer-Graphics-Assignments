#include "main.h"

#ifndef GOAL_H
#define GOAL_H


class Goal {
public:
    Goal() {}
    Goal(float x, float y, color_t color, string textureFile);
    glm::vec3 position;
    float rotation;
    double speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    
private:
    VAO *object;
};

#endif 
