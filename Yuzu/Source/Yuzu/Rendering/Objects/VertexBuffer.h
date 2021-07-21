#pragma once

namespace Yuzu
{

	class VertexBuffer
	{

	public:

		~VertexBuffer();

		VertexBuffer(void* data, unsigned int size, GLenum Usage);

		void SetNewData(void* data, const unsigned int size);

		void Bind() const;
	private:
		unsigned int m_RenderID;


	};
}
