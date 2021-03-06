#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#pragma region IMGUI
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl2.h>
#include  <imgui_internal.h>
