#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include <ctime>
#include <glm/glm.hpp>
#include "Shader.h"

class BlurPass
{
public:
	BlurPass() {}
 	~BlurPass() {}

	void Load() {
		std::vector<const GLchar*> uniformNames;

		//TEMPLATE uniformNames.push_back("lightDirection");
		//uniformNames.push_back("renderedTexture");
		//uniformNames.push_back("time");
		uniformNames.push_back("xBlur");
		uniformNames.push_back("yBlur");
		uniformNames.push_back("xScreen");
		uniformNames.push_back("yScreen");

		uniforms = shader.Load("BlurPass", uniformNames);
	}

	void Bind(float amount, vec2 screenSize) {
		shader.Bind();

		//TEMPLATE glUniform3f(uniforms["lightDirection"], 0.0f, 0.0f, 1.0f);
		//glUniform1f(uniforms["time"], (float)clock() / 250.0f);
		//glUniform1f(uniforms["xBlur"], (glm::sin(clock() / 500.0f) + 1.0f)*10.0f);
		//glUniform1f(uniforms["yBlur"], (glm::sin(clock() / 500.0f) + 1.0f)*10.0f);
		glUniform1f(uniforms["xBlur"], amount);
		glUniform1f(uniforms["yBlur"], amount);
		glUniform1f(uniforms["xScreen"], screenSize.x);
		glUniform1f(uniforms["yScreen"], screenSize.y);
		
	}

private:
	Shader shader = Shader();
	std::map<const GLchar*, GLuint> uniforms;

};
