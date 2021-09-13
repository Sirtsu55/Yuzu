#pragma once


#include "Yuzu/Core.h"
#include "Yuzu/Window/Application.h"
#include "Yuzu/Window/Window.h"
#include "Yuzu/World/World.h"
#include "Yuzu/World/CameraHandler.h"
#include "Yuzu/World/Entities/Entity.h"
#include "Yuzu/World/Components/Components.h"
#include "Yuzu/Rendering/Renderer/Renderer.h"
#include "Yuzu/Rendering/Renderer/BatchRenderer.h"
#include "Yuzu/Timer/FuncTimer.h"


#define YZ_APPLICATION(ClassName) Yuzu::Application* Yuzu::CreateApplication() { return new ClassName(); } 
