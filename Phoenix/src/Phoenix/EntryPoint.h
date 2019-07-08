#pragma once

#ifdef PHX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {

	Phoenix::Log::Init();
	PHX_CORE_WARN("Initialized Log!");
	PHX_CORE_TRACE("Hello!");

	Phoenix::Application* app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}

#endif