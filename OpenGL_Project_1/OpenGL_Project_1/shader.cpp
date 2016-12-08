#include "shader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "transform.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace cameraControl;

Shader::Shader(const std::string& filename)
{
	program = glCreateProgram();
	
	shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normal");


	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Program failed to link");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Invalid shader program ");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");

}


Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{

	glm::mat4 mvp = transform.GetMVP(camera);
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &mvp[0][0]);

	//glm::mat4 model = transform.GetModel();
	//glm::mat4 MVP = transform.GetMVP(camera);
	//glm::mat4 Normal = transform.GetModel();

	//glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	//glUniformMatrix4fv(uniforms[1], 1, GL_FALSE, &Normal[0][0]);
	//glUniform3f(uniforms[2], 0.0f, 0.0f, 1.0f);

	//glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	//glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, glm::value_ptr(mvp));
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
		std::cerr << "Error compiling shader type " << shaderType << std::endl;

	const GLchar* shaderSourceStrings[1];
	shaderSourceStrings[0] = text.c_str();
	//cout << "ShaderSourceString                : " << shaderSourceStrings[0] << endl;
	GLint shaderSourceStringlengths[1];
	shaderSourceStringlengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringlengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}