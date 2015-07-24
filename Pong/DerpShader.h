#pragma once
#include <GL/glew.h>
#include <vector>
#include <map>
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

class DerpShader
{
public:
	DerpShader() {};
	~DerpShader(){}

	void Load(){
		shader = Shader();
		
		std::vector<const GLchar*> uniformNames;
		
		uniformNames.push_back("MVP");
		//uniformNames.push_back("time");
		//uniformNames.push_back("Normal");
		//uniformNames.push_back("lightDirection");

		uniforms = shader.Load("DerpShader", uniformNames);
	};
	
	void Bind(Transform transform, const Camera& camera){
		shader.Bind();

		glm::mat4 MVP = transform.GetMVP(camera);
		glm::mat4 Normal = transform.GetModel();

		glUniformMatrix4fv(uniforms["MVP"], 1, GL_FALSE, &MVP[0][0]);
		//glUniformMatrix4fv(uniforms["Normal"], 1, GL_FALSE, &Normal[0][0]);
		//glUniform3f(uniforms["lightDirection"], 0.0f, 0.0f, 1.0f);
		//glUniform1ui(uniforms["time"], (unsigned int)Globals::time);

	};

private:
	Shader shader;
	std::map<const GLchar*, GLuint> uniforms;

};

