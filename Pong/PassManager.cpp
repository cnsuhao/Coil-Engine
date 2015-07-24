#include "PassManager.h"



PassManager::PassManager()
{
	//Standard settings
	CAPass_Amount = 0.0f;
	BlurPass_Amount = 1.0f;
	PCAPass_Amount = 1.0f;
	PCAPass_Position = vec2(0.5f);
	screenSize = vec2(Globals::windowWidth, Globals::windowHeight);

}


PassManager::~PassManager()
{
}

bool PassManager::Load()
{
	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	render_fbo = 0;
	glGenFramebuffers(1, &render_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, render_fbo);
	// The texture we're going to render to
	fbo_textures[0] = 0;
	fbo_textures[1] = 0;
	glGenTextures(2, &fbo_textures[0]);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, fbo_textures[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Globals::windowWidth, Globals::windowHeight, 0, GL_RGB, GL_FLOAT, 0);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB, Globals::windowWidth, Globals::windowHeight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/*
	glBindTexture(GL_TEXTURE_2D, fbo_textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Globals::windowWidth, Globals::windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, 2048, 2048);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	*/
	// The depth buffer
	//depthrenderbuffer = 0;
	//glGenRenderbuffers(1, &depthrenderbuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glBindTexture(GL_TEXTURE_2D, fbo_textures[1]);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, Globals::windowWidth, Globals::windowHeight);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbo_textures[0], 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbo_textures[1], 0);

	// Set the list of draw buffers.
	DrawBuffers[0] = { GL_COLOR_ATTACHMENT0 };
	//DrawBuffers[1] = { GL_DEPTH_ATTACHMENT  GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//MAKE PASS QUAD
	
	Vertex quadVerts[6] = {
		Vertex(vec3(-1.0, -1.0, 0),	vec2(0.0, 0.0), vec3(0,0,1.0)),
		Vertex(vec3(-1.0, 1.0, 0),	vec2(0.0, 1.0),	vec3(0,0,1.0)),
		Vertex(vec3(1.0, 1.0, 0),	vec2(1.0, 1.0),	vec3(0,0,1.0)),

		Vertex(vec3(-1.0, -1.0, 0),	vec2(0.0, 0.0), vec3(0,0,1.0)),
		Vertex(vec3(1.0, -1.0, 0),	vec2(1.0, 0.0),	vec3(0,0,1.0)),
		Vertex(vec3(1.0, 1.0, 0),	vec2(1.0, 1.0),	vec3(0,0,1.0))
	};
	

	/*Vertex quadVerts[3] = {
		Vertex(vec3(-1.0, -1.0, 0),	vec2(0.0, 0.0), vec3(0,0,1.0)),
		Vertex(vec3(-1.0, 4.0, 0),	vec2(0.0, 2.0),	vec3(0,0,1.0)),
		Vertex(vec3(4.0, -1.0, 0),	vec2(2.0, 0.0),	vec3(0,0,1.0)),
	};*/

	Quad = Mesh();
	Quad.Load(quadVerts, 6);
	//Quad.Load(quadVerts, 3);

	BasePassTex[0] = Texture();
	BasePassTex[0].Load(fbo_textures[0]);

	BasePassTex[1] = Texture();
	BasePassTex[1].Load(fbo_textures[1]);

	//Init shaders
	simplePass = SimplePass();
	simplePass.Load();
	blurPass = BlurPass();
	blurPass.Load();
	frostedPass = FrostedPass();
	frostedPass.Load();
	pcaPass = PCAPass();
	pcaPass.Load();
	caPass = CAPass();
	caPass.Load();
	ssaoPass = SSAOPass();
	ssaoPass.Load();
}

void PassManager::Bind()
{
	
	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, render_fbo);
	//glBindFramebuffer(GL_DEPTH_BUFFER, render_fbo);
	glViewport(0, 0, Globals::windowWidth, Globals::windowHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

}

void PassManager::Render()
{
	BasePassTex[0].Bind(0);
	BasePassTex[1].Bind(1);

	//Passes-----------
	//SSAO
	//ssaoPass.Bind();
	//Quad.Draw();

	//Point chromatic abberation
	pcaPass.Bind(PCAPass_Amount, PCAPass_Position);
	Quad.Draw();
	
	//Chromatic abberation
	caPass.Bind(CAPass_Amount);
	Quad.Draw();

	//Blur pass / Anti Aliasing
	blurPass.Bind(BlurPass_Amount, screenSize);
	Quad.Draw();




}

void PassManager::LastPass()
{
	//Frosted pass - LAST PASS
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Globals::windowWidth, Globals::windowHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	//BasePassTex.Bind(0);
	simplePass.Bind();
	Quad.Draw();

	//glClearTexImage()

}
