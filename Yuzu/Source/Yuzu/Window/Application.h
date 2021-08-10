#pragma once


namespace Yuzu
{
	class Window;
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Init();
		virtual void Start();
		virtual void OnUpdate(float DeltaTime);
		virtual void OnWidgetRender(float Deltatime);
		virtual void OnDestroy();
		
	protected:
		Sptr<Window> ApplicationWindow;
	};
	Application* CreateApplication();

}