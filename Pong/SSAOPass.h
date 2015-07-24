#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include "Shader.h"

class SSAOPass
{
public:
	SSAOPass() {}
	~SSAOPass() {}

	void Load() {
		std::vector<const GLchar*> uniformNames;

		//TEMPLATE uniformNames.push_back("lightDirection");

		uniforms = shader.Load("ssao", uniformNames);
	}

	void Bind() {
		shader.Bind();

		//TEMPLATE glUniform3f(uniforms["lightDirection"], 0.0f, 0.0f, 1.0f);

	}

private:
	Shader shader = Shader();
	std::map<const GLchar*, GLuint> uniforms;

};

