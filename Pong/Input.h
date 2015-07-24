#pragma once
#include <SDL2/SDL.h>
//#include <SDL2/SDL_events.h>
//#include <SDL2/SDL_keyboard.h>
//#include <SDL2/SDL_keycode.h>
//#include <SDL2/SDL_mouse.h>
#include <iostream>
//#include "Globals.h"


class Input
{
public:
	Input();
	~Input();

	void HandleInput();

	bool hasQuit = false;

};

