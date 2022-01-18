#include <iostream>
#include <string>
#include <future>

#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <dinput.h>
#include <tchar.h>
#pragma comment (lib, "d3d9.lib")

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "misc/cpp/imgui_stdlib.h"

#include "spdlog/spdlog.h"