#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <thread>
#include <iostream>
#include <ctime>
#include <vector>
#include <map>

#include "Globals.h"
#include "MainGame.h"

#include "PassManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "BlurPass.h"

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	/*
	Description:
	UPS: Updates per second
	FPS: Frames per second 
	0 = ∞
	*/
	void Run(float FPSLimit);

private:
	bool Load();
	void Update();
	void Render();
	void Unload();
	void ProcessInput();

	//Variables
	MainGame	mainGame = MainGame();
	int			fpscounter = 0, fpslastSec = 0;
	double		lastTime = 0.0;

	SDL_GLContext glContext;
	//Shader		aoShader;
	//GLuint      render_fbo;
	//GLuint      fbo_textures[3];
	//GLuint		depthrenderbuffer;
	//GLenum		DrawBuffers[1];
	//GLuint      quad_vao;
	//GLuint      points_buffer;

	//PASS
	//Mesh		Quad;
	//Texture		BasePassTex;
	//BlurPass	BlurPassShader;
	PassManager passManager;

};

