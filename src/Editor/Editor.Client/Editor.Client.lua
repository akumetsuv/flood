EditorClient = {}
EditorClient.name = "Editor.Client"

project "Editor.Client"

	kind "SharedLib"
	language "C#"
	
	location "."
	
	files
	{
		"Editor.Client.lua",
		"**.cs",
	}
	
	links
	{
		"System",
		"System.ComponentModel", 
		"System.ComponentModel.Composition",
		"EngineManaged",
		"EngineBindings",
		"Editor.Shared",
		"Editor.Server",
		"ServerManaged",
		"GUI" 
	}