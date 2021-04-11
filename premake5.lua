-- Workspace Accel ------------------------------

workspace "Accel"
	architecture "x64"
	startproject "SandBox"
	
	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

dynamicdef = "AC_DYLIB"
staticdef  = "AC_STLIB"

-- Vendor Libs --
  -- IncludeDir --
IncludeDir = {}
IncludeDir["SFML"] = "Accel/vendor/SFML/include"
  
  -- premake scripts include --
  -- null temp --

-- Accel --

project "Accel"
	location "Accel"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "acpch.h"
	pchsource "Accel/src/acpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/SFML/include",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AC_PLATFORM_WINDOWS",
			"AC_BUILD_DLL",
			dynamicdef,
			
			"SFML_STATIC"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}

	filter "configurations:Debug"
		defines "AC_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "AC_RELEASE"
		runtime "Release"
		optimize "On"
		

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Accel/vendor/SFML/include",
		"Accel/src",
	}

	links
	{
		"Accel",

		"opengl32.lib",
		"winmm.lib",
		"ws2_32.lib",
		
		"Accel/vendor/SFML/*.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AC_PLATFORM_WINDOWS",
			
			dynamicdef,
			"SFML_STATIC",
		}

	filter "configurations:Debug"
		defines "AC_DEBUG"
		runtime "Debug"
		symbols "On"
		

	filter "configurations:Release"
		defines "AC_RELEASE"
		runtime "Release"
		optimize "On"
		
