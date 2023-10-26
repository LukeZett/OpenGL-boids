#include "GL/glew.h"
#include <iostream>
#include <vector>

void render()
{

}

std::vector<GLfloat> grid(int x, int y)
{
	std::vector<GLfloat> points = {};
	float size_x = 1.0 / x;
	for (size_t i = 0; i < 1; i += size_x)
	{
		points.push_back(i);
		points.push_back(0);
		points.push_back(0);
		points.push_back(i);
		points.push_back(1);
		points.push_back(0);
	}
	return points;
}