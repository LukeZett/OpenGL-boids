#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ShaderCompiler.h"
#include <iostream>
#include "Drawing.h"
#include "tiny_obj_loader.h"
#include <chrono>
#include "Window.h"
#include "Application.h"

Window mainWindow = { Windowed, "Boids" };
Application application = (&mainWindow);

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
    else if (action == GLFW_RELEASE) {
        application.KeyRelease(key, scancode, mods);
    }
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    application.MouseMove(xpos, ypos);
}


int main(void)
{


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

    
    glEnable(GL_MULTISAMPLE);
    glfwSetKeyCallback(mainWindow.window, key_callback);
    glfwSetCursorPosCallback(mainWindow.window, cursor_position_callback);
    application.Init();

    /* Loop until the user closes the window */
    auto timestamp{ std::chrono::steady_clock::now() };

    while (!glfwWindowShouldClose(mainWindow.window)
        )
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        application.Draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(mainWindow.window);
        
        /* Poll for and process events */
        glfwPollEvents();
        auto timestamp2{ std::chrono::steady_clock::now() };
        const std::chrono::duration<float> duration = { timestamp2 - timestamp };
        timestamp = timestamp2;
        application.NextStep(duration.count());
    }

    glfwTerminate();
    return 0;
}

