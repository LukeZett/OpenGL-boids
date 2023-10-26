#pragma once
#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	std::cout << width << " x " << height << std::endl;
}


enum WindowMode
{
	Fullscreen,
	WindowedFullScreen,
	Windowed
};

class Window
{
private:
public:

	WindowMode mode;
	int height;
	int width;
	GLFWwindow* window;
	std::string name;

	Window(WindowMode mode, std::string name, int height = 0, int width = 0);
	void WindowInit();
	void ToggleFullScreen();
	void CreateWindow();
	~Window();
};


