#pragma once
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class ShaderManager 
{
public:
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"uniform vec3 u_Transform;"
		"void main() {"
		"  gl_Position = vec4(vp + u_Transform, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"uniform vec4 u_Color;"
		"void main() {"
		"  frag_colour = u_Color;"
		"}";

	void CompileShader(GLuint Shader, std::string FilePath, int ShaderType);
	void AttachShader(GLuint ShaderProgram, GLuint ShaderToAttach);
	void LinkProgram(GLuint ShaderProgram);
	void UseProgram(GLuint ShaderProgram);

private:
	std::string ReadShaderFile(std::string FilePath);
};