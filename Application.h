#pragma once
#include "Simulation.h"

class Application
{
private:
public:
	void Init();
	void NextStep(float deltaTime);
	void Draw();
	void KeyPress(int key, int scancode, int mods);
	void KeyRelease(int key, int scancode, int mods);
};

