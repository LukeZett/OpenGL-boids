#include "Simulation.h"
#include<iostream>
#include<cstdlib>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

using namespace std;

float randomFloat()
{
	return (float)(rand()) / ((float)(RAND_MAX) / 2) - 1.0;
}

float randomFloat01()
{
	return (float)(rand()) / ((float)(RAND_MAX));
}

// Function to scale a glm::vec2 to a given length
glm::vec2 scaleVectorToLength(const glm::vec2& vec, float desiredLength) {
	float currentLengthSquared = glm::length2(vec);
	float scaleFactor = (desiredLength * desiredLength) / currentLengthSquared;
	return vec * glm::sqrt(scaleFactor);
}




std::vector<boid> init_boids(int amount)
{
	auto result = std::vector<boid>();
	srand((unsigned)time(NULL));

	for (size_t i = 0; i < amount; i++)
	{
		float angle = (rand() % 360) * 3.141 / 180;

		float x = cos(angle);
		float y = sin(angle);

		boid new_boid = { glm::vec2(randomFloat(), randomFloat()), glm::vec2(x, y), 0, glm::vec3(randomFloat01(),randomFloat01(),randomFloat01())};
		result.push_back(new_boid);
	}
	result[result.size() - 1].rgb = { 1, 1, 1 };
	return result;
}

void next_step(std::vector<boid>& boids, behaviour flock_behavior)
{
	for (size_t i = 0; i < boids.size(); i++)
	{
		boids[i].pos = boids[i].pos + (boids[i].dir * 0.004f);
		
		glm::vec2 avg_pos = { 0, 0 };
		glm::vec2 avg_vlc = { 0, 0 };
		glm::vec2 avg_sep = { 0, 0 };
		glm::vec3 avg_color = { 0, 0, 0 };
		int neighbors = 0;
		int flock_size = 0;
		if (boids[i].pos.x > -0.90 && boids[i].pos.x < 0.90 && boids[i].pos.y > -0.90 && boids[i].pos.y < 0.90) {
			for (size_t j = 0; j < boids.size(); j++)
			{
				if (j == i)
				{
					continue;
				}
				boid &other = boids[j];
				float distance = glm::distance(boids[i].pos, other.pos);
				if (distance < flock_behavior.view_distance)
				{
					avg_vlc += other.dir;
					avg_pos += other.pos;
					auto dot_prod = glm::dot(other.dir, boids[i].dir);


					if (dot_prod > 0.9659 && dot_prod < 1)
					{
						avg_color += other.rgb;
						flock_size += 1;

					}

					if (distance < flock_behavior.separation_distance)
					{
						auto diff = boids[i].pos - other.pos;
						scaleVectorToLength(diff, 1 / distance);
						avg_sep -= diff;
					}

					neighbors += 1;
				}
			}

			if (flock_size > 0)
			{
				avg_color /= flock_size;
			}
			if (neighbors > 0)
			{
				avg_vlc /= neighbors;
				avg_pos /= neighbors;
				avg_sep /= neighbors;
				avg_color *= 0.01;
				avg_vlc *= 0.02;
				avg_pos *= 0.01;
				avg_sep *= 0.06;
			}
			glm::vec2 new_vel = { boids[i].dir.x + avg_vlc.x + avg_pos.x - avg_sep.x, boids[i].dir.y + avg_vlc.y + avg_pos.y - avg_sep.y };

			new_vel = scaleVectorToLength(new_vel, 1);


			boids[i].dir = new_vel;
			boids[i].rgb *= 0.99f;
			boids[i].rgb += avg_color;
			
		}

		if (boids[i].pos.x > 1)
		{
			boids[i].pos.x -= 2;
		}
		else if (boids[i].pos.x < - 1)
		{
			boids[i].pos.x += 2;
		}
		if (boids[i].pos.y > 1)
		{
			boids[i].pos.y -= 2;
		}
		else if (boids[i].pos.y < -1)
		{
			boids[i].pos.y += 2;
		}
	}
	return;
}
