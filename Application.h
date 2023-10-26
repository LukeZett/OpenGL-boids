#pragma once
#include <GL/glew.h>
#include "Simulation.h"
#include <glm/ext.hpp>
#include "ShaderCompiler.h"

struct Camera {
	glm::vec3 position;
	glm::vec3 looking_dir;
	float fov;
	float aspect_ratio;
	glm::vec3 up_dir = {0.0f, 1.0f, 0.0f};
	float z_near = 0.01f;
	float z_far = 100.0f;

	glm::mat4x4 GetPerpective()
	{
		return glm::perspective(fov, aspect_ratio, z_near, z_far);
	}

	glm::mat4x4 GetView()
	{
		return glm::lookAt(position, position + looking_dir, up_dir);
	}
};

class Application
{
private:
	int n;
	std::vector<boid> boids;
	behaviour flock_behavior;
	Camera camera;
	GLuint shader_program = 0;
public:
	Application();
	void Init();
	void NextStep(float deltaTime);
	void Draw();
	void KeyPress(int key, int scancode, int mods);
	void KeyRelease(int key, int scancode, int mods);
};

