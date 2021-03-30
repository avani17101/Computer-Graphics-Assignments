#include "main.h"

#ifndef HWALL_H
#define HWALL_H
#define GLM_ENABLE_EXPERIMENTAL

class Hwall {
public:
    Hwall() {}
    Hwall(float x1, float y1, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box;
    bounding_box_t return_bounding_box ();
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