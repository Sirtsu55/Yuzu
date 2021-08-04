#include "Core.h"
#include "VertexArray.h"


namespace Yuzu
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_RenderID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& Buffer, const VertexBufferLayout& layout)
	{
		glBindVertexArray(m_RenderID);
		Buffer.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;


		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);


			glEnableVertexAttribArray(i);

			offset += VertexBufferElement::GetSizeOfType(element.type) * element.count;

		}

	}
	

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}
}