#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include <GL/glew.h>

class texture
{
public:
	texture(const std::string& fileName);
	void Bind(unsigned int unit);
	virtual ~texture();

private:
	texture(const texture& texture) {}
	void operator=(const texture& texture) {}

	GLuint m_texture;
};

#endif

