#include "mesh.h"



mesh::mesh(vertex* vertices, unsigned int numVertices)
{
	drawCount = numVertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//locate vertex to buffer
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);//locate the specific attibute arrays
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

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