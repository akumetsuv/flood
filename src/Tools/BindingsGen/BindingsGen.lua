BindingsGen = {}
BindingsGen.name = "BindingsGen"

project "BindingsGen"

  kind "ConsoleApp"
  language "C#"
  location "."

  files { "**.cs", "./*.lua" }

  dependson { "Parser" }

  links
  {
    path.join(depsdir, "cxxi", "build", action, "lib", "Bridge"),
    path.join(depsdir, "cxxi", "build", action, "lib", "Generator"),
  }

