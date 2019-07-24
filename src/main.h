#ifndef MAIN_H
#define MAIN_H
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

float dist_between_objects(float xa,float ya,float za,float xb,float yb,float zb);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection2;
    glm::mat4 model2;
    glm::mat4 view2;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float width;
    float height;
    float depth;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);

extern float screen_zoom, screen_center_x, screen_center_y,camera_zoom;
extern int cam_view;
void reset_screen();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_Peach;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_GOLD;
extern const color_t COLOR_GreyL;
extern const color_t COLOR_Silver;
extern const color_t COLOR_Grey;
extern const color_t COLOR_Met;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_PURE;
extern const color_t COLOR_TAN;
extern const color_t COLOR_Cyan;
extern const color_t COLOR_WATER;
extern const color_t COLOR_CHOC;
extern const color_t COLOR_DGREEN;
extern const color_t COLOR_OLIVE;
extern const color_t COLOR_YGREEN;
extern const color_t COLOR_FGREEN;
extern const color_t COLOR_SGREEN;
extern const color_t COLOR_FIRE;
extern const color_t COLOR_Sienaa;
extern const color_t COLOR_Maroon;
extern const color_t COLOR_Lime;
extern const color_t COLOR_Yell;
#endif
