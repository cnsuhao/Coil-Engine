#pragma once
#include <SDL2/SDL.h>
#include <string>
//#include <vector>
#include "Input.h"

using namespace std;

enum class GameState	{PLAY, EXIT};
enum class MouseState	{ATTRACTING, IDLE, REPELLING};

namespace Globals
{
	
	//Window
	static SDL_Window*		gameWindow;
	static Input			input;

	//Window Startup settings
	static const char *		windowTitle		= "OpenGL - Pong - 1.0";
	static int				windowWidth		= 1920;//1280;
	static int				windowHeight	= 1080;//720;
	static bool				Fullscreen		= true;
	static int				FPSLimit		= 60;
	static int				AASamples		= 0;

	//Game
	static GameState		curGamestate	= GameState::PLAY;
	static MouseState		curMouseState	= MouseState::IDLE;
	static double			deltaTime		= 0.0;
	//static const int		MAXparticles	= 10000;
	//static vector<Particle> particles;

}
