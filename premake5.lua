workspace "Phoenix"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
IncludeDir = {}
IncludeDir["GLFW"] = "Phoenix/vendor/GLFW/include"
IncludeDir["GLAD"] = "Phoenix/vendor/GLAD/include"
IncludeDir["imgui"] = "Phoenix/vendor/imgui"
IncludeDir["glm"] = "Phoenix/vendor/glm"

group "deps"
	include "Phoenix/vendor/GLFW"
	include "Phoenix/vendor/GLAD"
	include "Phoenix/vendor/imgui"

group ""

project "Phoenix"
	location "Phoenix"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
	pchheader "pcheaders.h"
	pchsource "Phoenix/src/pcheaders.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"GLAD",
		"imgui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"PHX_PLATFORM_WINDOWS",
			"PHX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "PHX_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "PHX_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "PHX_DIST"
		runtime "Release"
		optimize "on"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Phoenix/vendor/spdlog/include",
		"Phoenix/src",
		"Phoenix/vendor",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"Phoenix"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"PHX_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "PHX_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "PHX_RELEASE"
		runtime "Release"
		optimize "on"
	
	filter "configurations:Dist"
		defines "PHX_DIST"
		runtime "Release"
		optimize "on"