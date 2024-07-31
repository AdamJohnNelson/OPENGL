#include "ShaderManager.h"

void ShaderManager::CompileShader(GLuint Shader, std::string FilePath, int ShaderType)
{
    if (ShaderType == GL_VERTEX_SHADER)
    {
        std::string ShaderText = ReadShaderFile(FilePath);
        char* Text = &ShaderText[0];

        glShaderSource(Shader, 1, &Text, NULL);
        glCompileShader(Shader);
        int result;
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length = 0;
            char InfoLog[1024] = "";
            glGetShaderInfoLog(Shader, 1024, &length, InfoLog);
            std::cout << "Vertex shader failed to compile:" << std::endl;
            std::cout << InfoLog << std::endl;
        }
        else
        {
            std::cout << "Vertex shader compiled successfully." << std::endl;
        }
    }
    else if (ShaderType == GL_FRAGMENT_SHADER)
    {
        std::string ShaderText = ReadShaderFile(FilePath);
        char* Text = &ShaderText[0];

        glShaderSource(Shader, 1, &Text, NULL);
        glCompileShader(Shader);
        int result;
        glGetShaderiv(Shader, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            std::cout << "Fragment shader failed to compile." << std::endl;
            int length = 0;
            char InfoLog[1024] = "";
            glGetShaderInfoLog(Shader, 1024, &length, InfoLog);
            std::cout << InfoLog << std::endl;
        }
        else
        {
            std::cout << "Fragment shader compiled successfully." << std::endl;
        }
    }
    else
    {
        std::cout << "Shader type not currently supported in ComplileShader function of ShaderManager" << std::endl;
    }

}

void ShaderManager::AttachShader(GLuint ShaderProgram, GLuint ShaderToAttach)
{
    glAttachShader(ShaderProgram, ShaderToAttach);
}

void ShaderManager::LinkProgram(GLuint ShaderProgram)
{
    glLinkProgram(ShaderProgram);;
}

void ShaderManager::UseProgram(GLuint ShaderProgram)
{
    glUseProgram(ShaderProgram);
}

std::string ShaderManager::ReadShaderFile(std::string FilePath)
{
    std::ifstream InputFile;
    std::string ShaderLine = "";
    std::string ShaderText = "";
    InputFile.open(FilePath);
    if (!InputFile.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return "";
    }
    while (std::getline(InputFile, ShaderLine))
    {
        ShaderText += ShaderLine + '\n';
    }
    std::cout << ShaderText << std::endl;

    return ShaderText;
}

