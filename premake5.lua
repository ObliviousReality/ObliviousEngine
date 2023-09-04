workspace "ObliviousEngine"
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
IncludeDir["entt"] = "ObliviousEngine/vendor/entt/include"
IncludeDir["GLFW"] = "ObliviousEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "ObliviousEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "ObliviousEngine/vendor/imgui"
IncludeDir["glm"] = "ObliviousEngine/vendor/glm"
IncludeDir["stb_image"] = "ObliviousEngine/vendor/stb_image"



include "ObliviousEngine/vendor/GLFW"
include "ObliviousEngine/vendor/Glad"
include "ObliviousEngine/vendor/imgui"



project "ObliviousEngine"
	location "ObliviousEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir  ("bin/" .. outputdir .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "oepch.h"
	pchsource "ObliviousEngine/src/oepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
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
		"%{IncludeDir.entt}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"OE_PLATFORM_WINDOWS",
			"OE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "OE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OE_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"ObliviousEngine/src",
		"ObliviousEngine/vendor",
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
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "OE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "OE_DIST"
		runtime "Release"
		optimize "on"
