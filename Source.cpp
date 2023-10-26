#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ShaderCompiler.h"
#include <iostream>
#include "Drawing.h"
#include "tiny_obj_loader.h"
#include <chrono>
#include "Window.h"
#include "Application.h"

std::filesystem::path wd;
behaviour bh = { normal, 0.1f, 0.05f };
Window mainWindow = { Windowed, "Boids" };
Application application;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_F11:
            mainWindow.ToggleFullScreen();
            break;
        default:
            application.KeyPress(key, scancode, mods);
            break;
        }
    }
    else {
        application.KeyRelease(key, scancode, mods);
    }
}


int main(void)
{
    wd = std::filesystem::current_path();

    /* Initialize the library */

    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    mainWindow.WindowInit();
    if (!mainWindow.window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */

    auto err = glewInit();
    if (err != GLEW_OK)
        return -1;

    shader_program = CreateShaderProgram(GL_VERTEX_SHADER, wd / "Shaders" / "main.vert", GL_FRAGMENT_SHADER, wd / "Shaders" / "main.frag");
    compute_shader_program = CreateShaderProgram(GL_COMPUTE_SHADER, wd / "Shaders" / "helloGPU.comp");

    
    glEnable(GL_MULTISAMPLE);
    glfwSetKeyCallback(mainWindow.window, key_callback);

    int n = 400;
    
    auto boids = init_boids(n);

    GLuint boid_buffer = 0;
    glGenBuffers(1, &boid_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, boid_buffer);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(boid), &boids[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(boid), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(boid), (const void*) (offsetof(boid, dir)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(boid), (const void*)(offsetof(boid, rgb)));
    glVertexAttribDivisor(0, 6);
    glVertexAttribDivisor(2, 6);
    glVertexAttribDivisor(1, 6);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mainWindow.window)
        )
    {
        auto start{ std::chrono::steady_clock::now() };

        /* Render here */
        
        next_step(boids, bh);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_program);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, n * 6);


        /* Swap front and back buffers */
        glfwSwapBuffers(mainWindow.window);
        glBufferSubData(GL_ARRAY_BUFFER, 0, n * sizeof(boid), &boids[0]);
        
        /* Poll for and process events */
        glfwPollEvents();
        auto end{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds{ end - start };
        std::cout << elapsed_seconds.count() << "s\n";

    }

    glfwTerminate();
    return 0;
}

