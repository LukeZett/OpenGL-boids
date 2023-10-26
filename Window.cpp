#include "Window.h"




Window::Window(WindowMode mode, std::string name, int height, int width)
{
    this->name = name;
    this->mode = mode;
    this->height = height;
    this->width = width;
    this->window = nullptr;
}

void Window::WindowInit()
{
    CreateWindow();
}

void Window::ToggleFullScreen()
{
    auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videomode = glfwGetVideoMode(monitor);
    if (mode == Fullscreen) {
        mode = Windowed;
        width = videomode->width / 2;
        height = videomode->height / 2;
        glfwSetWindowMonitor(window, NULL, width / 2, height / 2, width, height, videomode->refreshRate);
    }
    else if (mode == Windowed)
    {
        width = videomode->width;
        height = videomode->height;
        mode = Fullscreen;
        glfwSetWindowMonitor(window, monitor, 0, 0, width, height, videomode->refreshRate);
    }
}

void Window::CreateWindow()
{
    if (window != nullptr)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videomode = glfwGetVideoMode(monitor);
    width = videomode->width;
    height = videomode->height;

    glfwWindowHint(GLFW_SAMPLES, 4);

    if (mode == Fullscreen)
    {
        window = glfwCreateWindow(width, height, name.c_str(), monitor, NULL);
    }
    else if (mode == WindowedFullScreen)
    {
        window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    }
    else
    {
        window = glfwCreateWindow(width / 2, height / 2, name.c_str(), NULL, NULL);
    }
    if (!window)
    {
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window()
{
    glfwDestroyWindow(window);
}
