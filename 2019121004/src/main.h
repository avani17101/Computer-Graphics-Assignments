#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint loadBMP_custom(const char * imagepath);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, const GLfloat *uv_buffer_data, GLenum fill_mode, string textureFile);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *uv_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode, string textureFile);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *uv_buffer_data, const color_t color, GLenum fill_mode, string textureFile);
void       draw3DObject(struct VAO *vao);
void drawPlayer(struct VAO *vao, GLuint texture);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;
    GLuint UVBuffer;
    GLenum PrimitiveMode;
    GLenum FillMode;
    GLuint Texture;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();


// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_GREY_RING;
extern const color_t COLOR_MAGNET;
extern const color_t COLOR_METALLIC_GOLD;
extern const color_t COLOR_OLD_GOLD;
extern const color_t COLOR_LIGHT_BLUE;

extern const color_t COLOR_ORANGERED;
extern const color_t COLOR_GOLDEN_BROWN;
extern const color_t COLOR_OLIVE;
extern const color_t COLOR_SKIN;

extern const color_t COLOR_BLUE;
extern const color_t COLOR_MAGENTA;


extern const color_t COLOR_WOOD;

#endif
