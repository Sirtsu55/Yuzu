#pragma once


namespace Yuzu
{
	class Texture
	{
	private:
		std::string m_FilePath;
		unsigned int m_RenderID;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
		bool m_valid;

		void SendData(GLenum InternalFormat, GLenum Format);

	public:
		Texture(const std::string& path);
		Texture() = default;
		~Texture();

		void FreeImage();


		void Bind(unsigned int slot = 0) const;


		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		bool IsValid() const { return m_valid; }



	};

}