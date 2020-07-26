workspace "screech"
    language "C"
    toolset "gcc"
    cdialect "gnu99"
    warnings "Extra"
    targetdir "bin/"
    includedirs { "include" }
    configurations { "Default" }

project "screech"
    kind "SharedLib"
    files { "source/screech.c" }

project "screech.test"
    kind "ConsoleApp"
    files { "test/screech.test.c" }
    links { "screech" }
