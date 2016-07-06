#pragma once

#include <stdexcept>
#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


void GLFW_key_callback(GLFWwindow* window, int keyCode, int scanCode, int action, int modifiers);

void GLFW_error_callback(int errorCode, const char* msg);
