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
	
project "Phoenix"
	location "Phoenix"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"PHX_PLATFORM_WINDOWS",
			"PHX_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "PHX_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "PHX_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "PHX_DIST"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
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
		"Phoenix/src"
	}
	
	links
	{
		"Phoenix"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.18362.0"
		
		defines
		{
			"PHX_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "PHX_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "PHX_RELEASE"
		optimize "On"
	
	filter "configurations:Dist"
		defines "PHX_DIST"
		optimize "On"