#pragma once
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
#include <string>
#include <GL/glew.h>

GLuint loadDDS(const std::string& imagepath);

class Texture
{
public:
	Texture();

	void Load(const std::string& fileName);
	void Load(GLuint loadedTex);
	void Bind(int unit);

	virtual ~Texture();
protected:
private:
	//Texture(const Texture& texture) {}
	//void operator=(const Texture& texture) {}

	GLuint m_texture;
};

