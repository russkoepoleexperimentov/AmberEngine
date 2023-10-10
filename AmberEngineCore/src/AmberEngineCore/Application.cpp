#include "AmberEngineCore/Application.hpp"
#include "AmberEngineCore/Log.hpp"
#include "glad/glad.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace AmberEngine {
	Application::Application() 
	{

	}

	Application::~Application()
	{
	
	}

	int Application::start(unsigned int window_width, unsigned int window_height, const char* title) 
	{
        LOG_INFO("Welcome to Amber Engine");

        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
        {
            LOG_CRITICAL("Failed to initialize OpenGL (GLAD)");
            return -1;
        }

        glClearColor(1, 0, 0, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            on_update();
        }

        glfwTerminate();
        return 0;
	}
}

