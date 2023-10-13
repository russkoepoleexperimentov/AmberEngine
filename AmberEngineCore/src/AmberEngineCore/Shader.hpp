#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "AmberEngineCore/Log.hpp"

namespace AmberEngine 
{
	class Shader
	{
	private:
		unsigned int _id;
		void checkCompileErrors(unsigned int shader, std::string type);
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
	};
}