# Yuzu
A 2D Game engine in progress


This engine is a game engine made with OpenGL.


Rename "Sandbox" Project to whatever name you want.
Set the Application Project as a Startup Projet.

Reference for how to setup: SandboxApplication.h,  SandboxApplication.cpp

Include "Yuzu.h"
Create an Application class that inherits from Yuzu::Application.
Create a Window and A Yuzu::World.
Set World As current and Set Window Application as this eg. ApplicationWindow->SetApplication(this);

In your Application Start() Funtion call Yuzu::RunGameLoop() in the very end.
Yuzu::RunGameLoop() will run the gameloop and call Application OnUpdate Function and do engine background Stuff.

Call World->OnUpdate() in your Application OnUpdate function. 
And Call Yuzu::_FuncTimerCore::UpdateTimers() if You use any FunctionTimers.

