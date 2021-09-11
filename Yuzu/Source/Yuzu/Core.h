#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <memory>
#include <queue>
#include <thread>
#include <chrono>
#include <list>
#include <thread>
#include <tuple>
#include <optional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>
#include <glad/glad.h>


#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Log/Logger.h"
#include "Timer/Timers.h"

#include "Rendering/Objects/ElementBuffer.h"
#include "Rendering/Objects/Shader.h"
#include "Rendering/Objects/Texture.h"


#ifndef MACROS_SETUP

#define MACROS_SETUP



//---------------------------------------
//Shared Pointers
//---------------------------------------

template<typename T>
using Sptr = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Sptr<T> CreateSptr(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

//---------------------------------------
//Weak Pointer
//---------------------------------------

template<typename T>
using Wkptr = std::weak_ptr<T>;


//---------------------------------------
//Unique Pointers
//---------------------------------------

template<typename T>
using Uptr = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Uptr<T> CreateUptr(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}



//---------------------------------------
//Casting
//---------------------------------------

#define ReCast reinterpret_cast

//---------------------------------------
//Logging
//---------------------------------------

#define LOG 1

#if LOG


//CORE LOGGER
#define YZC_CRITICAL(...) Yuzu::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define YZC_ERROR(...)    Yuzu::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YZC_WARN(...)     Yuzu::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YZC_INFO(...)     Yuzu::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YZC_TRACE(...)    Yuzu::Log::GetCoreLogger()->trace(__VA_ARGS__)
						  
//APPLICATION LOGER		  
#define YZA_CRITICAL(...) Yuzu::Log::GetClientLogger()->critical(__VA_ARGS__)
#define YZA_ERROR(...)    Yuzu::Log::GetClientLogger()->error(__VA_ARGS__)
#define YZA_WARN(...)     Yuzu::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YZA_INFO(...)     Yuzu::Log::GetClientLogger()->info(__VA_ARGS__)
#define YZA_TRACE(...)    Yuzu::Log::GetClientLogger()->trace(__VA_ARGS__)

#endif // LOG


//---------------------------------------
//Profiling
//---------------------------------------

#define PROFILING 1
#if PROFILING
	#define YZ_PROFILE(Name) Yuzu::ScopedTimer Timer##__LINE__(Name)
	#define YZ_PROFILE_FUNCTION() Yuzu::ScopedTimer Timer##__LINE__(__FUNCTION__)
	#define YZ_PROFILE_FUNCTION_SIG() Yuzu::ScopedTimer Timer##__LINE__(__FUNCSIG__)

#else

	#define YZ_PROFILE(Name)
	#define YZ_PROFILE_FUNCTION()
	#define YZ_PROFILE_FUNCTION_SIG()

#endif // PROFILING


//---------------------------------------
//-----DEBUG-----------------------------
//---------------------------------------



#define DEBUG_LEVEL 4


#if DEBUG_LEVEL > 0
static void GLAPIENTRY OpenGLErrorCallback(GLenum source​, GLenum type​, GLuint id​,
	GLenum severity​, GLsizei length​,
	const GLchar* message​, const void* userParam)
{
#if DEBUG_LEVEL > 0
	if (severity​ == GL_DEBUG_SEVERITY_HIGH)
	{
		YZC_ERROR("[OpenGL] {}", message​);
	}
#endif
#if DEBUG_LEVEL > 1

	else if (severity​ == GL_DEBUG_SEVERITY_MEDIUM)
	{
		YZC_WARN("[OpenGL] {}", message​);
	}
#endif
#if DEBUG_LEVEL > 2

	else if (severity​ == GL_DEBUG_SEVERITY_LOW)
	{
		YZC_INFO("[OpenGL] {}", message​);
	}
#endif
#if DEBUG_LEVEL > 3

	else if (severity​ == GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		YZC_TRACE("[OpenGL] {}", message​);
	}
#endif

}




#endif // DEBUG_LEVEL != 0

#endif // !MACROS_SETUP

//---------------------------------------
//---------------------------------------
