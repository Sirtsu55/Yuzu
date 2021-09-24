#include "Core.h"
#include "Shader.h"


namespace Yuzu
{
    CoreShader::CoreShader(const std::string& filepath)
        :m_ProgramID(0)
    {

        ShaderSource source = ParseShader(filepath);
        m_ProgramID = CreateShader(source.VertexSource, source.FragmentSource);


    }

    CoreShader::CoreShader(const ShaderSource& Source)
    {
        m_ProgramID = CreateShader(Source.VertexSource, Source.FragmentSource);
    }

    CoreShader::CoreShader()
        :m_ProgramID(0)
    {
    }

    CoreShader::~CoreShader()
    {
        glDeleteProgram(m_ProgramID);
    }

    void CoreShader::Bind() const
    {
        for (const auto&[Slot, Texture] : m_TextureMap)
        {
            Texture->Bind(Slot);
        }
        glUseProgram(m_ProgramID);
    }

    void CoreShader::SetInt(const char* name, const int val)  const
    {

        glUniform1i(GetUniformLocation(name), val);

    }

    void CoreShader::SetVec4(const char* name, const glm::vec4& value) const
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);

    }

    void CoreShader::SetVec3(const char* name, const glm::vec3& value) const
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void CoreShader::SetMat4(const char* name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    void CoreShader::SetMat3(const char* name, const glm::mat3& matrix) const
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    int CoreShader::GetUniformLocation(const char* name) const
    {
        if (m_UniformMap.find(name) != m_UniformMap.end())
            return m_UniformMap[name];
        int loc = glGetUniformLocation(m_ProgramID, name);

        if (loc == -1)
            YZC_WARN("Uniform does not exist : name = {}", name);


        m_UniformMap[name] = loc;
        return loc;
    }

    void CoreShader::InsertTexture(Sptr<Texture> NewTex, unsigned char slot)
    {
        m_TextureMap[slot] = NewTex;
    }

    unsigned int CoreShader::CreateShader(const std::string VertexSource, std::string FragmentSource)
    {

        unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexSource);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentSource);


        unsigned int program = glCreateProgram();

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);
        int success;
        int lenght;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &lenght);


        if (!success)
        {
            char* message = (char*)alloca(lenght);
            glGetProgramInfoLog(program, lenght, NULL, message);

            YZC_ERROR("Program Link Failed: {}", message);

        }



        return program;

    }

    ShaderSource CoreShader::ParseShader(std::string Path)
    {

        std::string outVertexSource;
        std::string outFragmentSource;

        std::ifstream file;
        std::string line;

        std::cout << Path;

        char Current = 0;
        file.open(Path.c_str());

        while (std::getline(file, line))
        {
            if (line == "!Vertex!")
                Current = 1;
            else if (line == "!Fragment!")
                Current = 0;

            else if (Current == 1)
                outVertexSource += line + "\n";
            else if (Current == 0)
                outFragmentSource += line + "\n";
        }

        file.close();

        std::cout << outVertexSource << " \n ---------------------------------- \n " << outFragmentSource << std::endl;


        return { outVertexSource, outFragmentSource };
    }

    unsigned int CoreShader::CompileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);

        const char* src = source.c_str();

        glShaderSource(id, 1, &src, NULL);
        glCompileShader(id);

        int result;

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;

            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            char* message = (char*)alloca(length * sizeof(char));

            glGetShaderInfoLog(id, length, &length, message);

            YZC_ERROR("Shader Compile Error : {}", message);


            glDeleteShader(id);

            return 0;


        }

        return id;
    }
}

