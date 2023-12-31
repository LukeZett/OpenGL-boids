#pragma once
#include <GL/glew.h>
#include "Simulation.h"
#include <glm/ext.hpp>
#include "ShaderCompiler.h"
#include "Window.h"

struct Camera {
	glm::vec3 position;
	glm::vec3 looking_dir;
	float fov;
	float aspect_ratio;
	glm::vec3 up_dir = {0.0f, 1.0f, 0.0f};
	float z_near = 0.01f;
	float z_far = 100.0f;
	float horizontalAngle = 3.141;
	float verticalAngle = 0;

	glm::mat4x4 GetPerpective()
	{
		return glm::perspective(fov, aspect_ratio, z_near, z_far);
	}

	glm::mat4x4 GetView()
	{
		return glm::lookAt(position, position + looking_dir, up_dir);
	}
	void UpdateDirection() {
		looking_dir = {
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		};
	}
};

struct CameraMovement {
	bool forward = false;
	bool backward = false;
	bool right = false;
	bool left = false;
};


class Application
{
private:
	int n;
	Window *mainWindow;
	CameraMovement cameraMovement;
	std::vector<boid> boids;
	behaviour flock_behavior;
	Camera camera;
	GLuint shader_program = 0;
	glm::mat4x4 pM;
	glm::mat4x4 vM;
	glm::mat4x4 mM;
	glm::vec<2, double> cursorPos;
	bool disabledCursor;

public:
	Application(Window *window);
	void Init();
	void NextStep(float deltaTime);
	void Draw();
	void KeyPress(int key, int scancode, int mods);
	void KeyRelease(int key, int scancode, int mods);
	void MouseMove(float x, float y);
	void MoveCamera(float deltatime);
};

