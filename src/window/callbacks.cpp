#include "callbacks.hpp"

//Key inputs
void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    if (key == Escape && action == Hold && !glfwWindowShouldClose(glfwWindow))
    {
        glfwSetWindowShouldClose((glfwWindow), true);

        std::cout << "The program has shut down" << std::endl;
    }
}

//Character input
void charCallback(GLFWwindow* glfwWindow, unsigned int keyCode)
{

}

//Character mod input
void charModCallback(GLFWwindow* glfwWindow, unsigned int keyCode, int modifierKey)
{

}

//Cursor position
void cursorPosCallback(GLFWwindow* glfwWindow, double xPos, double yPos)
{

}

//Cursor enter
void cursorEnterCallback(GLFWwindow* glfwWindow, int entered)
{

}

//Mouse buttons
void mButtonCallback(GLFWwindow* glfwWindow, int mButton, int action, int mods)
{

}

//Mouse scroll
void scrCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
{

}

//Window maximized
void windowMaximizedCallback(GLFWwindow* glfwWindow, int windowMaximized)
{

}

//Window size
void windowSizeCallback(GLFWwindow* glfwWindow, int nWidth, int nHeight)
{

}

//Framebuffer size
void frameBufferSizeCallback(GLFWwindow* glfwWindow, int windowFramebufferWidth, int windowFrameBufferHeight)
{

}
