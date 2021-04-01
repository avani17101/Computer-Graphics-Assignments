#include "main.h"

#ifndef SCOREBOARD_H
#define SOREBOARD_H


class Scoreboard {
public:
    Scoreboard() {}
    Scoreboard(float x, float y, color_t color, string textureFile);
    glm::vec3 position;
    int score, screen_x, screen_y, lives, range, max_range, tasks_completed, light;
    double speed;
    float rotation, direction, offset;
    
    GLuint Texture_up;
    GLuint Texture_down;
    GLuint Texture_left;
    GLuint Texture_right;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    
private:
    VAO *object;
};

#endif // EMPTY_H
