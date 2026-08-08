#pragma once

#include <functional>

#include "3D/Vertex.h"
#include "3D/Material.h"
#include "3D/Light.h"
#include "3D/Shader.h"
#include "3D/PerspectiveTest.h"

#include "RendererInterface.h"

#if defined(PLATFORM_WINDOWS)
#include <windows.h>
#include "Windows/WindowsGDI.h"
#include "Windows/WindowsRSI.h"
#include "Windows/WindowsGLContext.h"

#include "OpenGL/OpenGLDevice.h"
#include "OpenGL/OpenGLRSI.h"

#include "Glad/glad.h"
#include "Stb/stb_easy_font.h"

#endif

using namespace GER;
