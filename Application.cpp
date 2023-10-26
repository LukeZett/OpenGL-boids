#include "Application.h"

Application::Application(Window *window) : mainWindow(window)
{
    camera = {
        {0.f, 0.f, 5.f},
        {0,0,-1},
        70.f,
        16.f / 9
    };
}

void Application::Init()
{

    auto wd = std::filesystem::current_path();
    n = 400;

    shader_program = CreateShaderProgram(GL_VERTEX_SHADER, wd / "Shaders" / "main.vert", GL_FRAGMENT_SHADER, wd / "Shaders" / "main.frag");
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

    pM = camera.GetPerpective();
    vM = camera.GetView();
    mM = glm::identity<glm::mat4x4>();

    glProgramUniformMatrix4fv(shader_program, 0, 1, GL_FALSE, glm::value_ptr(mM));
    glProgramUniformMatrix4fv(shader_program, 1, 1, GL_FALSE, glm::value_ptr(vM));
    glProgramUniformMatrix4fv(shader_program, 2, 1, GL_FALSE, glm::value_ptr(pM));
}

void Application::NextStep(float deltaTime)
{
    MoveCamera(deltaTime);
    next_step(boids, flock_behavior, deltaTime / 2);
    glBufferSubData(GL_ARRAY_BUFFER, 0, n * sizeof(boid), &boids[0]);
}

void Application::Draw()
{
    vM = camera.GetView();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(vM));
    glUseProgram(shader_program);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, n * 6);
}

void Application::KeyPress(int key, int scancode, int mods)
{
    switch (key)
    {
    case GLFW_KEY_W: cameraMovement.forward = true; break;
    case GLFW_KEY_S: cameraMovement.backward = true; break;
    case GLFW_KEY_A: cameraMovement.left = true; break;
    case GLFW_KEY_D: cameraMovement.right = true; break;
    case GLFW_KEY_ENTER: glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); break;
    default:
        break;
    }
}

void Application::KeyRelease(int key, int scancode, int mods)
{
    switch (key)
    {
    case GLFW_KEY_W: cameraMovement.forward = false; break;
    case GLFW_KEY_S: cameraMovement.backward = false; break;
    case GLFW_KEY_A: cameraMovement.left = false; break;
    case GLFW_KEY_D: cameraMovement.right = false; break;
    case GLFW_KEY_ENTER: glfwSetInputMode(mainWindow->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;
    default:
        break;
    }
}
void Application::MoveCamera(float deltatime)
{
    int speed = 5;
    if (cameraMovement.forward && !cameraMovement.backward)
    {
        camera.position += camera.looking_dir * (deltatime * speed);
    }
    else if (!cameraMovement.forward && cameraMovement.backward){
        camera.position -= camera.looking_dir * (deltatime * speed);
    }

    if (cameraMovement.right && !cameraMovement.left)
    {
        camera.position += glm::cross(camera.looking_dir, camera.up_dir) * (deltatime * speed);
    }
    else if (!cameraMovement.right && cameraMovement.left) {
        camera.position -= glm::cross(camera.looking_dir, camera.up_dir) * (deltatime * speed);
    }
}

