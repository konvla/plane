#ifndef KEYBOARD
#define KEYBOARD

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"object.h"

extern bool is_fire;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void Plane_speed_change(GLFWwindow* window, object* Plane);

#endif