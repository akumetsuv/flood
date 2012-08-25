Pipeline = {}

function FindFBX()
	
end

project "Pipeline"

	kind "StaticLib"
	builddeps { "Core", "Resources" }
	
	pchheader "Pipeline/API.h"
	pchsource "../src/Pipeline/Pipeline.cpp"
	
	files
	{
		"Pipeline.lua",
		"../inc/Pipeline/**.h",
		"../src/Pipeline/**.cpp",
	}
	
	vpaths
	{
		[""] = { "../src/", "../inc/" },
		["Importers"] = { "**/*Importer*" },
		["Importers/Milkshape"] = { "**/*Milkshape*" },
		["Importers/FBX"] = { "**/*FBX*" },
		["Processors"] = "**/*Processor*",
		["Processors/Image"] = "**/*ImageProcessor*",
		["Processors/Mesh"] = "**/*MeshProcessor*",
	}

	includedirs
	{
		"../src/",
		"../inc/",
		"../dep/nvtt/include",
		"../dep/FbxSdk/2012.1/include",
	}

	Pipeline.libdirs =
	{
		"../dep/FbxSdk/2012.1/lib/vs2010/x86",
	}
	
	Pipeline.links =
	{
	}

	Pipeline.deps =
	{
		"NVIDIATextureTools"
	}
	
	deps(Pipeline.deps)