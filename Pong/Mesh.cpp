#include "Mesh.h"



Mesh::Mesh()
{
	
}


Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, drawCount);
	glBindVertexArray(0);

	

}

void Mesh::Unload()
{
	glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Load(Vertex vertices[], unsigned int numVertices)
{
	cout << "Loading Mesh..." << endl;
	drawCount = numVertices;

	//Unpacking Vertices 1 - List init
	vector<vec3> positions = vector<vec3>();
	vector<vec2> texcoords = vector<vec2>();
	vector<vec3> normals = vector<vec3>();

	//Unpacking Vertices 2 - Extraction
	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back	(vertices[i].position);
		texcoords.push_back	(vertices[i].texcoord);
		normals.push_back	(vertices[i].normal);
	}

	//Generating the buffers for the mesh
	//VAO
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,			//Layout ID
		3,			//pieces of data
		GL_FLOAT,	//Type
		GL_FALSE,	//normalized
		0,			//stride
		0);			//offset

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * texcoords.size(), &texcoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	
}
