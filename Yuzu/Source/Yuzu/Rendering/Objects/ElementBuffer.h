#pragma once

namespace Yuzu
{
	class ElementBuffer
	{


	private:

		GLenum m_DataType;
		unsigned int m_RenderID;
		unsigned int m_count;

	public:
		ElementBuffer(void* indices, unsigned int count, unsigned int usage, GLenum datatype);
		~ElementBuffer();
		void Bind() const;
		GLenum GetDataType() const { return m_DataType; }
		unsigned int GetCount() const { return m_count; }

	};

}