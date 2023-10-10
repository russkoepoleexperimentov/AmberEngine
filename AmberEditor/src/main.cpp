#include <iostream>
#include <memory>
#include "AmberEngineCore/Application.hpp"

class EditorApplication : public AmberEngine::Application
{
	virtual void on_update() override 
	{
		std::cout << "Update frame " << frame++ << std::endl;
	}

	int frame = 0;
};

int main()
{
	auto app = std::make_unique<EditorApplication>();
	
	int code = app->start(1024, 768, "Amber Editor");

	std::cin.get();
	return code;
}