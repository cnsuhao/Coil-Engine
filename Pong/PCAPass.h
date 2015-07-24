#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <ctime>
#include "Shader.h"

class PCAPass
{
public:
	PCAPass() {}
	~PCAPass() {}

	void Load() {
		std::vector<const GLchar*> uniformNames;

		//TEMPLATE uniformNames.push_back("lightDirection");
		uniformNames.push_back("Amount");
		uniformNames.push_back("Xpos");
		uniformNames.push_back("Ypos");

		//uniformNames.push_back("time");

		uniforms = shader.Load("PCAPass", uniformNames);
	}

	void Bind(float amount, vec2 pos) {
		shader.Bind();

		//TEMPLATE glUniform3f(uniforms["lightDirection"], 0.0f, 0.0f, 1.0f);
		glUniform1f(uniforms["Amount"], amount * glm::sin(clock()));
		glUniform1f(uniforms["Xpos"], glm::cos(clock()*2));
		glUniform1f(uniforms["Ypos"], glm::sin(clock()));

	}

private:
	Shader shader = Shader();
	std::map<const GLchar*, GLuint> uniforms;

};
