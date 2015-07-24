#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include <ctime>
#include "Globals.h"
#include "Shader.h"

class CAPass
{
public:
	CAPass() {}
	~CAPass() {}

	void Load() {
		std::vector<const GLchar*> uniformNames;

		//TEMPLATE uniformNames.push_back("lightDirection");
		uniformNames.push_back("Amount");

		//uniformNames.push_back("time");

		uniforms = shader.Load("CAPass", uniformNames);
	}

	void Bind(float amount) {
		shader.Bind();

		//TEMPLATE glUniform3f(uniforms["lightDirection"], 0.0f, 0.0f, 1.0f);
		glUniform1f(uniforms["Amount"], amount);

	}

private:
	Shader shader = Shader();
	std::map<const GLchar*, GLuint> uniforms;

};
