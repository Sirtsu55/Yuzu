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


	private:

	};

	Application* CreateApplication();


}