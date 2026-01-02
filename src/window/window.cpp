#include "window.hpp"

Window::Window(int windowWidth, int windowHeight, const char *windowTitle) : width(windowWidth), height(windowHeight), title(windowTitle)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // REQUIRED on mac
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
   #endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Faild to initialize GLEW" << std::endl;
    }
}

// Just in case I need this, in while loop in main.
void Window::run()
{
    
}

// Just in case I need this, after while loop in main.
void Window::cleanUp()
{
    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }    
}

int Window::getWidth() const
{
    return width;
}

int Window::getHeight() const
{
    return height;
}

void Window::setWidth(int nWidth) 
{
    this->width = nWidth;
} 

void Window::setHeight(int nHeight)
{
    this->height = nHeight;
}

const std::string Window::getTitle() const 
{
    return title;
}

GLFWwindow* Window::getWindow() const
{
    return window;
}
