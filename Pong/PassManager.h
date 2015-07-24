#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

//#include "Globals.h"
#include "Mesh.h"
#include "Texture.h"
#include "Passes.h"

class PassManager
{
public:
	PassManager();
	~PassManager();

	bool Load();
	void Bind();
	void Render();
	void LastPass();

	
	float	CAPass_Amount;
	float	BlurPass_Amount;
	float	PCAPass_Amount;
	vec2	PCAPass_Position;
	vec2	screenSize;

private:
	GLuint      render_fbo;
	GLuint      fbo_textures[2];
	GLuint		depthrenderbuffer;
	GLenum		DrawBuffers[1];

	//Objects
	Mesh		Quad;
	Texture		BasePassTex[2];

	//Passes
	SimplePass	simplePass;
	BlurPass	blurPass;
	FrostedPass	frostedPass;
	PCAPass		pcaPass;
	CAPass		caPass;
	SSAOPass	ssaoPass;

};

