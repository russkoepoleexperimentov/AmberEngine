#pragma once

#include "AmberEngineCore/Event.hpp"
#include "AmberEngineCore/Log.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <string>
#include <functional>

namespace AmberEngine {
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(BaseEvent&)>;

		Window(std::string title, unsigned int width, unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window operator=(const Window&) = delete;
		Window operator=(Window&&) = delete;

		void on_update();
		unsigned int get_width() const { return m_data.width; }
		unsigned int get_height() const { return m_data.height; }

		void set_event_callback(const EventCallbackFn& callback)
		{
			m_data.eventCallbackFn = callback;
		}

	private:
		struct WindowData 
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			EventCallbackFn eventCallbackFn;
		};

		int init();
		void shutdown();

		GLFWwindow* m_pWindow = nullptr;
		WindowData m_data;
	};
}