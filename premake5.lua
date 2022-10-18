workspace "ObliviousEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["entt"] = "ObliviousEngine/vendor/entt/include"
IncludeDir["glm"] = "ObliviousEngine/vendor/glm"
IncludeDir["GLFW"] = "ObliviousEngine/vendor/GLFW/include"

include "ObliviousEngine/vendor/GLFW"

project "ObliviousEngine"
	location "ObliviousEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "oepch.h"
	pchsource "ObliviousEngine/src/oepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/SDL/include",
		"%{prj.name}/vendor/SDLTTF/include",
		"%{prj.name}/vendor/SDLImage/include",
		"%{prj.name}/vendor/SDLMixer/include",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}"
	}

	libdirs
	{
		"%{prj.name}/vendor/SDL/lib/x64",
		"%{prj.name}/vendor/SDLTTF/lib/x64",
		"%{prj.name}/vendor/SDLImage/lib/x64",
		"%{prj.name}/vendor/SDLMixer/lib/x64"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"SDL2",
		"SDL2main",
		"SDL2_ttf",
		"SDL2_image",
		"SDL2_mixer"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OE_PLATFORM_WINDOWS",
			"OE_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OE_RELEASE"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OE_DIST"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"ObliviousEngine/vendor/spdlog/include",
		"ObliviousEngine/vendor/SDL/include",
		"ObliviousEngine/vendor/SDLTTF/include",
		"ObliviousEngine/vendor/SDLImage/include",
		"ObliviousEngine/vendor/SDLMixer/include",
		"ObliviousEngine/src",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"ObliviousEngine/vendor/SDL/lib/x64",
		"ObliviousEngine/vendor/SDLTTF/lib/x64",
		"ObliviousEngine/vendor/SDLImage/lib/x64",
		"ObliviousEngine/vendor/SDLMixer/lib/x64"
	}

	links
	{
		"ObliviousEngine",
		"SDL2",
		"SDL2main",
		"SDL2_ttf",
		"SDL2_image",
		"SDL2_mixer"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"OE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OE_RELEASE"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OE_DIST"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"
