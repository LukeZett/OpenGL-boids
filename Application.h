#pragma once
#include <GL/glew.h>
#include "Simulation.h"

class Application
{
private:
	int n;
	std::vector<boid> boids;
	behaviour flock_behavior;
public:
	void Init();
	void NextStep(float deltaTime);
	void Draw();
	void KeyPress(int key, int scancode, int mods);
	void KeyRelease(int key, int scancode, int mods);
};

