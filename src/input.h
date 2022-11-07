#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

extern bool firstMouse;
extern float deltaTime;
extern Camera camera;
extern GLFWwindow* window;
extern int middle_x;
extern int middle_y;

extern bool Qpressed;
extern bool Qsignal;
extern bool Epressed;
extern bool Esignal;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif
