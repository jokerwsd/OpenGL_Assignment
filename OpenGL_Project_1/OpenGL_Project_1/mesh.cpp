#include "mesh.h"
#include <vector>

mesh::mesh(vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}

	//locate vertex to buffer
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);//locate the specific attibute arrays
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);//locate the specific attibute arrays
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

	glBindVertexArray(0);
}


mesh::~mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void mesh::draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);//draw all the data we have in the buffer
	glBindVertexArray(0);
}