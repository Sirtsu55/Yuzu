#include "Core.h"
#include "Texture.h"
#include "stb/stb_image.h"

namespace Yuzu
{

	Texture::Texture(const std::string& path)
		: m_FilePath(path), m_RenderID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
	{
		if (path != "")
		{
			m_valid = true;
			glGenTextures(1, &m_RenderID);
			glBindTexture(GL_TEXTURE_2D, m_RenderID);


			stbi_set_flip_vertically_on_load(true);

			m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
			if (stbi_failure_reason() != NULL)
				std::cout << stbi_failure_reason() << std::endl;
			else
				std::cout << "No Failiure" << std::endl;

			if (m_LocalBuffer && (m_BPP == 4))
			{
				SendData(GL_RGBA8, GL_RGBA);
			}
			else if (m_LocalBuffer && (m_BPP == 3))
			{
				SendData(GL_RGB8, GL_RGB);
			}
			else
			{
				YZC_WARN("No Data In {}", m_FilePath);
			}

		}
		else
		{
			m_valid = false;
			YZC_WARN("TexturePathBad", m_FilePath);
		}

		
		FreeImage();
	}

	void Texture::SendData(GLenum InternalFormat, GLenum Format)
	{				
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, m_LocalBuffer);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
	}


	void Texture::FreeImage()
	{
		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
			m_LocalBuffer = nullptr;
		}

	}
	Texture::~Texture()
	{
		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
		}
		glDeleteTextures(1, &m_RenderID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RenderID);

	}

}