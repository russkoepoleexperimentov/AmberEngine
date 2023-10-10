#include <iostream>
#include <memory>
#include "AmberEngineCore/Application.hpp"

class EditorApplication : public AmberEngine::Application
{
	virtual void on_update() override 
	{
	}
};

int main()
{
	auto app = std::make_unique<EditorApplication>();
	
	int code = app->start(1024, 768, "Amber Editor");

	
	return code;
	//move-семантика, smart ptr, pragma once
}