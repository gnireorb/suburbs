workspace ("suburbs")
   startproject ("suburbs")
   systemversion ("10.0")
   cppdialect ("C++20")
   toolset ("v143")
   defines { "_CRT_SECURE_NO_WARNINGS" }
   configurations { "Debug", "Release" }

project ("imgui")
   location ("include/%{prj.name}")
   kind ("StaticLib")
   language ("C++")
   targetdir ("bin/%{cfg.buildcfg}")
   includedirs { "include/%{prj.name}" }
   files { "include/%{prj.name}/backends/imgui_impl_dx9.cpp", "include/%{prj.name}/backends/imgui_impl_win32.cpp", "include/%{prj.name}/imgui.cpp", "include/%{prj.name}/imgui_tables.cpp", "include/%{prj.name}/imgui_demo.cpp", "include/%{prj.name}/imgui_widgets.cpp", "include/%{prj.name}/imgui_draw.cpp", "include/%{prj.name}/misc/cpp/imgui_stdlib.cpp" }

project ("suburbs")
   location ("suburbs")
   kind ("ConsoleApp")
   language ("C++")
   targetdir ("bin/%{cfg.buildcfg}")
   objdir ("bin/obj/%{cfg.buildcfg}/%{prj.name}")

   disablewarnings { "4244" }
   PrecompiledHeaderInclude = "common.hpp"
   PrecompiledHeaderSource = "%{prj.name}/src/common.cpp"

   includedirs { "%{prj.name}/src", "include/json/single_include", "include/spdlog/include", "include/imgui", "include/imgui/backends" }
   files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp" }

   links { "imgui" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
