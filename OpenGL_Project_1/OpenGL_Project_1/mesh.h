#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

struct vertex
{
public: 
	vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)	
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}
	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class mesh
{
public:
	mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	mesh(const std::string& filename);

	void draw();
	virtual ~mesh();
private:
	void InitMesh(const IndexedModel& model);
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;
};

#endif
