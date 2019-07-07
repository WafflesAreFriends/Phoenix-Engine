#pragma once

#include "Core.h"

namespace Phoenix {

	class PHOENIX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Defined in client
	Application* CreateApplication();

}