#pragma once


namespace Yuzu
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

	private:

	};

	Application* CreateApplication();


}