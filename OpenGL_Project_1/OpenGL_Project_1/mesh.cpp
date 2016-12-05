#include "mesh.h"
#include "obj_loader.h"
#include <vector>

mesh::mesh(const std::string& filename)
{
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	InitMesh(model);
}

mesh::mesh(vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{

	IndexedModel model;
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	InitMesh(model);

#if 0	
	drawCount = numIndices;
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
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);//locate the specific attibute arrays
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

#endif
}


mesh::~mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void mesh::InitMesh(const IndexedModel& model)
{
	drawCount = model.indices.size();
	
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);//locate the specific attibute arrays
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(1);//locate the specific attibute arrays
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(2);//locate the specific attibute arrays
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);//discribe the array data type

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void mesh::draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);//draw all the data we have in the buffer
	glBindVertexArray(0);
}