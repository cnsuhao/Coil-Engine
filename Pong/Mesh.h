#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace glm;
using namespace std;

struct Vertex
{
	vec3 position;
	vec2 texcoord;
	vec3 normal;

	Vertex(vec3 position, vec2 texcoord, vec3 normal)
	{
		this->position	= position;
		this->texcoord	= texcoord;
		this->normal	= normal;
	}

};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	
	NUM_BUFFERS
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	
	void Load(Vertex vertices[], unsigned int numVertices);
	void Draw();
	void Unload();

private:
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	GLuint drawCount;

};

