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
IncludeDir["Glad"] = "ObliviousEngine/vendor/Glad/include"
IncludeDir["imgui"] = "ObliviousEngine/vendor/imgui"


include "ObliviousEngine/vendor/GLFW"
include "ObliviousEngine/vendor/Glad"
include "ObliviousEngine/vendor/imgui"


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
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"


	}

	libdirs
	{
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"imgui"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OE_PLATFORM_WINDOWS",
			"OE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
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
		"ObliviousEngine/src",
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
	}

	links
	{
		"ObliviousEngine",
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
