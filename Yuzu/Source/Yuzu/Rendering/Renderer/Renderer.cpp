#include "Core.h"
#include "Renderer.h"
namespace Yuzu
{
	void Renderer::Draw(const Yuzu::VertexArray& VertArr, const Yuzu::ElementBuffer& ElementBuf, const Yuzu::Shader& Shader) const
	{
		Shader.Bind();
		VertArr.Bind();
		ElementBuf.Bind();

		glDrawElements(GL_TRIANGLES, ElementBuf.GetCount(), ElementBuf.GetDataType(), NULL);


	}
	void Renderer::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}




}