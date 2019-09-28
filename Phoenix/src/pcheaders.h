#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Phoenix/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

#ifdef PHX_PLATFORM_WINDOWS
	#include <Windows.h>
#endif