workspace ("suburbs")
   startproject ("suburbs")
   systemversion ("10.0")
   cppdialect ("C++20")
   toolset ("v143")
   defines { "_CRT_SECURE_NO_WARNINGS" }
   configurations { "Debug", "Release" }

project ("suburbs")
   location ("suburbs")
   
   kind ("ConsoleApp")
   language ("C++")

   targetdir ("bin/%{cfg.buildcfg}")
   objdir ("bin/obj/%{cfg.buildcfg}/%{prj.name}")

   disablewarnings { "4244" }

   PrecompiledHeaderInclude = "common.hpp"
   PrecompiledHeaderSource = "%{prj.name}/src/common.cpp"
   
   includedirs { "%{prj.name}/src" }

   links { "ImGui" }

   files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
