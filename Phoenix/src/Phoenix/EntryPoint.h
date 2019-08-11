#pragma once

#ifdef PHX_PLATFORM_WINDOWS // Defines platform will be used on

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {

	Phoenix::Log::Init();
	PHX_CORE_WARN("Initialized Log.");

	Phoenix::Application* app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}

#endif