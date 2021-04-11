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
		--"MultiProcessorCompile"
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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "default"
	
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
	
	links
	{
		"opengl32.lib",
		"winmm.lib",
		"ws2_32.lib",
		"gdi32.lib",
		
		"Accel/vendor/SFML/flac.lib",
		"Accel/vendor/SFML/freetype.lib",
		"Accel/vendor/SFML/ogg.lib",
		"Accel/vendor/SFML/openal32.lib",
		
		"Accel/vendor/SFML/vorbisenc.lib",
		"Accel/vendor/SFML/vorbisfile.lib",
		"Accel/vendor/SFML/vorbis.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AC_PLATFORM_WINDOWS",
			staticdef,
			
			"SFML_STATIC"
		}

		--postbuildcommands 
		--{
		--		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		--}

	filter "configurations:Debug"
		defines "AC_DEBUG"
		runtime "Debug"
		symbols "On"

		links
		{
			"Accel/vendor/SFML/sfml-window-s-d.lib",
			"Accel/vendor/SFML/sfml-system-s-d.lib",
			"Accel/vendor/SFML/sfml-graphics-s-d.lib",
			"Accel/vendor/SFML/sfml-audio-s-d.lib",
			"Accel/vendor/SFML/sfml-network-s-d.lib",
		}

	filter "configurations:Release"
		defines "AC_RELEASE"
		runtime "Release"
		optimize "On"
		
		links
		{
			"Accel/vendor/SFML/sfml-window-s.lib",
			"Accel/vendor/SFML/sfml-system-s.lib",
			"Accel/vendor/SFML/sfml-graphics-s.lib",
		}

project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "default"
	
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
		"gdi32.lib",
		
		"Accel/vendor/SFML/flac.lib",
		"Accel/vendor/SFML/freetype.lib",
		"Accel/vendor/SFML/ogg.lib",
		"Accel/vendor/SFML/openal32.lib",
		
		"Accel/vendor/SFML/vorbisenc.lib",
		"Accel/vendor/SFML/vorbisfile.lib",
		"Accel/vendor/SFML/vorbis.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AC_PLATFORM_WINDOWS",
			
			staticdef,
			"SFML_STATIC"
		}

	filter "configurations:Debug"
		defines "AC_DEBUG"
		runtime "Debug"
		symbols "On"
		
		links
		{
			"Accel/vendor/SFML/sfml-window-s-d.lib",
			"Accel/vendor/SFML/sfml-system-s-d.lib",
			"Accel/vendor/SFML/sfml-graphics-s-d.lib",
			"Accel/vendor/SFML/sfml-audio-s-d.lib",
			"Accel/vendor/SFML/sfml-network-s-d.lib",
		}


	filter "configurations:Release"
		defines "AC_RELEASE"
		runtime "Release"
		optimize "On"
		
		links
		{
			"Accel/vendor/SFML/sfml-window-s.lib",
			"Accel/vendor/SFML/sfml-system-s.lib",
			"Accel/vendor/SFML/sfml-graphics-s.lib",
		}

