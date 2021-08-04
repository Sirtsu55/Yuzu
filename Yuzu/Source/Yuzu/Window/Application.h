#pragma once


namespace Yuzu
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
		virtual void OnUpdate(float DeltaTime);
		virtual void OnWidgetRender(float Deltatime);
		virtual void OnDestroy();
	private:
		
	};

	Application* CreateApplication();

}