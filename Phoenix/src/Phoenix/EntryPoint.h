#pragma once

#ifdef PHX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {
	printf("Phoenix Engine");
	Phoenix::Application* app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}

#endif