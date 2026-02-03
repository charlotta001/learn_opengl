#include "config.h"

#ifndef FUNCTION_H
#define FUNCTION_H


void window_pos_callback(GLFWwindow* window, int width, int height);
GLuint make_module(const std::string &shaderPath,int shaderModule);
GLuint make_shader(const std::string &vertexPath, const std::string &fragmentPath);

#endif