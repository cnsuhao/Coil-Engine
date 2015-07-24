#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include <ctime>
#include "Shader.h"

class FrostedPass
{
public:
	FrostedPass() {}
	~FrostedPass() {}

	void Load() {
		std::vector<const GLchar*> uniformNames;

		//TEMPLATE uniformNames.push_back("lightDirection");
		//uniformNames.push_back("renderedTexture");
		uniformNames.push_back("time");

		uniforms = shader.Load("FrostedPass", uniformNames);
	}

	void Bind() {
		shader.Bind();

		//TEMPLATE glUniform3f(uniforms["lightDirection"], 0.0f, 0.0f, 1.0f);
		glUniform1f(uniforms["time"], (float)clock()/250.0f);

	}

private:
	Shader shader = Shader();
	std::map<const GLchar*, GLuint> uniforms;

};
