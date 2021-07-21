#include "Core.h"
#include "ElementBuffer.h"
#include "VertexBufferLayout.h"
namespace Yuzu
{
	ElementBuffer::ElementBuffer(void* indices, unsigned int count, unsigned int usage, GLenum datatype)
		:m_count(count), m_DataType(datatype)
	{
		glGenBuffers(1, &m_RenderID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * Yuzu::VertexBufferElement::GetSizeOfType(m_DataType), indices, usage);
		
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &m_RenderID);
	}

	void ElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}
}
