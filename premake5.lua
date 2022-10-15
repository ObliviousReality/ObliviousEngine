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

project "ObliviousEngine"
	location "ObliviousEngine"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.entt}"
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
		"SDL2",
		"SDL2main",
		"SDL2_ttf",
		"SDL2_image",
		"SDL2_mixer"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OE_PLATFORM_WINDOWS",
			"OE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "OE_DIST"
		optimize "On"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ObliviousEngine/vendor/spdlog/include",
		"ObliviousEngine/vendor/SDL/include",
		"ObliviousEngine/vendor/SDLTTF/include",
		"ObliviousEngine/vendor/SDLImage/include",
		"ObliviousEngine/vendor/SDLMixer/include",
		"ObliviousEngine/src",
		"%{IncludeDir.entt}"
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "OE_DIST"
		optimize "On"
	