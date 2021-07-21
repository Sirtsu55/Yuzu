#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


namespace Yuzu
{

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void AddBuffer(const VertexBuffer& Buffer, const VertexBufferLayout& layout);
		void Bind() const;


	private:
		unsigned int m_RenderID;

	};

}