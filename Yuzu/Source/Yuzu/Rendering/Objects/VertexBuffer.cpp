#include "Core.h"
#include "VertexBuffer.h"


namespace Yuzu
{
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);

	}

	VertexBuffer::VertexBuffer(void* data, unsigned int size, GLenum Usage)
	{
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ARRAY_BUFFER, size, data, Usage);
	}



	void VertexBuffer::SetNewData(void* data, const unsigned int size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);

	}

}