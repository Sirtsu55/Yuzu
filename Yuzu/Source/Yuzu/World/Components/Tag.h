#pragma once


namespace Yuzu
{
	struct TagComponent
	{
		TagComponent(const std::string name) : Name(name) {}
		TagComponent() = default;
		~TagComponent() = default;

		TagComponent(const TagComponent&) = default;
		
		std::string Name;
		

	};

}