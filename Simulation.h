#pragma once
#include <vector>
#include <glm/glm.hpp>

enum boid_action
{
	normal,
	freeroam,
};

struct behaviour
{
	boid_action action;
	float view_distance;
	float separation_distance;
};

struct boid {
	glm::vec2 pos;
	glm::vec2 dir;
	int angle;
	glm::vec3 rgb;
};

std::vector<boid> init_boids(int amount);

void next_step(std::vector<boid> &boids, behaviour flock_behavior);