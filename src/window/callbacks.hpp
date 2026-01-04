//std
#include <stdio.h>
#include <iostream>
#include <string>

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

//Project headers
#include "keyCode.h"

//Pragma
#pragma once

// PURPOSE : Defines functions for various GLFW window calls.

//Key inputs
void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);

//Character input
void charCallback(GLFWwindow* glfwWindow, unsigned int keyCode);

//Character mod input
void charModCallback(GLFWwindow* glfwWindow, unsigned int keyCode, int modifierKey);

//Cursor position
void cursorPosCallback(GLFWwindow* glfwWindow, double xPos, double yPos);

//Cursor enter
void cursorEnterCallback(GLFWwindow* glfwWindow, int entered);

//Mouse buttons
void mButtonCallback(GLFWwindow* glfwWindow, int mButton, int action, int mods);

//Mouse scroll
void scrCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset);

//Window maximized
void windowMaximizedCallback(GLFWwindow* glfwWindow, int windowMaximized);

//Window size
void windowSizeCallback(GLFWwindow* glfwWindow, int nWidth, int nHeight);

//Framebuffer size
void frameBufferSizeCallback(GLFWwindow* glfwWindow, int windowFramebufferWidth, int windowFrameBufferHeight);

