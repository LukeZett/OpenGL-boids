#include "Application.h"

void Application::Init()
{
    n = 400;

    boids = init_boids(n);
    flock_behavior = { normal, 0.1f, 0.05f };

    GLuint boid_buffer = 0;
    glGenBuffers(1, &boid_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, boid_buffer);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(boid), &boids[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(boid), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(boid), (const void*)(offsetof(boid, dir)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(boid), (const void*)(offsetof(boid, rgb)));
    glVertexAttribDivisor(0, 6);
    glVertexAttribDivisor(2, 6);
    glVertexAttribDivisor(1, 6);
}

void Application::NextStep(float deltaTime)
{
    next_step(boids, flock_behavior, deltaTime / 2);
    glBufferSubData(GL_ARRAY_BUFFER, 0, n * sizeof(boid), &boids[0]);
}

void Application::Draw()
{
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, n * 6);
}

void Application::KeyPress(int key, int scancode, int mods)
{
}

void Application::KeyRelease(int key, int scancode, int mods)
{
}
