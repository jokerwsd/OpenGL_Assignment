#ifndef _METHODS_H
#define _METHODS_H

#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <stdio.h>

using namespace std;

class methods
{
public:
	methods();
	~methods();
	bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);
	char *textFileRead(char *fn);
};

#endif
