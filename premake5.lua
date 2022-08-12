workspace "ObliviousEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/vendor/SDL/include"
	}

	libdirs
	{
		"%{prj.name}/vendor/SDL/lib/x64"
	}

	links
	{
		"SDL2",
		"SDL2main"
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
		"ObliviousEngine/src"
	}

	libdirs
	{
		"ObliviousEngine/vendor/SDL/lib/x64"
	}

	links
	{
		"ObliviousEngine",
		"SDL2",
		"SDL2main"
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
	