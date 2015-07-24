#pragma once
#include <iostream>
#include <map>
#include <ctime>
#include "Globals.h"
#include "Mesh.h"
#include "DerpShader.h"
#include "Texture.h"

using namespace std;

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Load();
	void Update();
	void Render();
	void Unload();

};

