#pragma once
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include "Transform.h"

class Shader
{
public:
	Shader();

	std::map<const GLchar*, GLuint> Load(const std::string& fileName, std::vector<const GLchar*> uniforms);
	void Bind();
	void Update();

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	//void operator=(const Shader& shader) {}
	//Shader(const Shader& shader);

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	//GLuint m_uniforms[NUM_UNIFORMS];
};
