#include "AmberEngineCore/Window.hpp"

#include "AmberEngineCore/Shader.hpp"

namespace AmberEngine {

    static bool s_GLFW_initialized = false;

    Window::Window(std::string title, unsigned int width, unsigned int height)
        : m_data({ std::move(title), width, height })
	{
		int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
	}

	Window::~Window() 
	{
		shutdown();
	}


    unsigned int VBO, VAO, EBO;
    std::unique_ptr<Shader> pShaderProgram;

	int Window::init() 
	{
        LOG_INFO("Creating window {0} with size {1}x{2}", m_data.title, m_data.width, m_data.height);

        if (s_GLFW_initialized == false)
        {
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialize GLFW!");
                return -1;
            }
            s_GLFW_initialized = true;
        }

        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        
        if (!m_pWindow)
        {
            LOG_CRITICAL("Can't create window {0} with size {1}x{2}", m_data.title, m_data.width, m_data.height);
            glfwTerminate();
            return -2;
        }

        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to initialize OpenGL (GLAD)");
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow, 
            [](GLFWwindow* pWindow, int width, int height) 
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(m_pWindow, 
            [](GLFWwindow* pWindow, double x, double y) 
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(m_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

        glfwSetFramebufferSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                glViewport(0, 0, width, height);
            }
        );

        pShaderProgram = std::make_unique<Shader>("res/default.vs", "res/default.fs");


        float vertices[] = {
             0.5f,  0.5f, 0.0f,  // top right
             0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return 0;
	}

	void Window::shutdown() 
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}

	void Window::on_update() 
	{
        glClearColor(1, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        pShaderProgram->use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
	}
}