#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <GL/glew.h>

class shader
{
public:
	shader(const std::string& filename);
	void Bind();

	virtual ~shader();


	GLuint shader::CreateShader(const std::string& text, GLenum shaderType);
	std::string shader::LoadShader(const std::string& fileName);
	void shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint program;
	GLuint shaders[NUM_SHADERS];
};

#endif