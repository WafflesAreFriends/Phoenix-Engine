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

include "Phoenix/vendor/GLFW"
include "Phoenix/vendor/GLAD"
include "Phoenix/vendor/imgui"

project "Phoenix"
	location "Phoenix"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"PHX_PLATFORM_WINDOWS",
			"PHX_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
		
	filter "configurations:Debug"
		defines "PHX_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "PHX_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "PHX_DIST"
		runtime "Release"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
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
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"Phoenix"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"PHX_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "PHX_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "PHX_RELEASE"
		runtime "Release"
		optimize "On"
	
	filter "configurations:Dist"
		defines "PHX_DIST"
		runtime "Release"
		optimize "On"