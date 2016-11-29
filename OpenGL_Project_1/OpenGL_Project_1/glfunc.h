#ifndef _GLFUNC_H
#define _GLFUNC_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "methods.h"
#include "window.h"


class glfunc
{
public:
	glfunc();
	glfunc(int _width, int _height);
	virtual ~glfunc();
	bool initGL();
	bool resizeGL(int width, int height);
	bool renderGL(GLFWwindow* window);

private:
	int width;
	int height;
	// Read our .obj file
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals; 
};

#endif