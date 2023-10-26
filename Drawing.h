#pragma once

int shader_program = 0;
int compute_shader_program = 0;

class ViewPort
{
public:
	int LocX;
	int LocY;
	int Width;
	int Height;
	ViewPort(int x, int y, int width, int height);
	~ViewPort();

private:

};

ViewPort::ViewPort(int x, int y, int width, int height)
{
	LocX = x;
	LocY = y;
	Width = width;
	Height = height;
}

ViewPort::~ViewPort()
{
}

ViewPort viewport = ViewPort(0,0,0,0);
GLuint texture = 0;

std::vector<GLfloat> grid(int x, int y);

void render();