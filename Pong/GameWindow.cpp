#include "GameWindow.h"

GameWindow::GameWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

GameWindow::~GameWindow()
{
	SDL_Quit();
}

void GameWindow::Run(float FPSLimit)
{
	if (Load() == false)
	{
		return;
	}

	while (Globals::curGamestate != GameState::EXIT)
	{
		ProcessInput();
		Update();
		Render();	
		if (Globals::FPSLimit != 0)
		{
			SDL_Delay(1000 / Globals::FPSLimit);
		}

	}

	Unload();
}

bool GameWindow::Load()
{
	// Settings
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,	32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,	32);

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, Globals::AASamples);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	
	
	Globals::gameWindow = SDL_CreateWindow(
		Globals::windowTitle,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Globals::windowWidth,
		Globals::windowHeight,
		SDL_WINDOW_OPENGL
		);

	if (Globals::Fullscreen)
	{
		SDL_SetWindowFullscreen(Globals::gameWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	}

	//Window
	if (Globals::gameWindow == NULL)
	{
		cout << "FAILED to create an SDL2 window!" << endl;
		return false;
	}

	//Context
	glContext = SDL_GL_CreateContext(Globals::gameWindow);
	if (glContext == NULL)
	{
		cout << "FAILED to create an SDL_GL context" << endl;
		return false;
	}

	//GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "FAILED to initialize GLEW!" << endl;
		return false;
	}

	//CREATING THE RENDER TARGET 
	passManager = PassManager();
	if (passManager.Load() == false)
	{
		return false;
	}

	//Clear color
	glClearColor(0.1, 0.1, 0.1, 0.1);
	
	//Depth testing
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	
	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ADD glBlendFunc(GL_ONE, GL_ONE);

	//Anti aliasing 
	glEnable(GL_MULTISAMPLE);

	//glPointSize(2.0f);

	//Load MainGame
	mainGame.Load();

	return true;
}

void GameWindow::ProcessInput()
{
	SDL_Event event;


	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.                                                  */
	while (SDL_PollEvent(&event)) {
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
		switch (event.type) {
		case SDL_KEYDOWN:
			//printf("Key press detected\n");
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_PLUS:		passManager.CAPass_Amount += 1.0f; break;
			case SDLK_KP_MINUS:		passManager.CAPass_Amount -= 1.0f; break;
			case SDLK_t:			passManager.PCAPass_Amount = 3.0f; break;
			case SDLK_b:			
				passManager.BlurPass_Amount == 1.0f ? passManager.BlurPass_Amount = 0.0f : passManager.BlurPass_Amount = 1.0f;
				break;
			}
			break;

		case SDL_KEYUP:
			//printf("Key release detected\n");
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:	Globals::curGamestate = GameState::EXIT; break;
			case SDLK_t:			passManager.PCAPass_Amount = 0.0f; break;
			case SDLK_F11:		
				Globals::Fullscreen ? 
					SDL_SetWindowFullscreen(Globals::gameWindow, SDL_WINDOW_OPENGL) : 
					SDL_SetWindowFullscreen(Globals::gameWindow, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN) ;  
				Globals::Fullscreen = !Globals::Fullscreen;
				break;
			
			}
			break;

		case SDL_QUIT:
			Globals::curGamestate = GameState::EXIT;
			//hasQuit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				Globals::curMouseState = MouseState::ATTRACTING;
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{
				Globals::curMouseState = MouseState::REPELLING;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (Globals::curMouseState == MouseState::ATTRACTING)
				{
					Globals::curMouseState = MouseState::IDLE;
				}
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (Globals::curMouseState == MouseState::REPELLING)
				{
					Globals::curMouseState = MouseState::IDLE;
				}
			}
			break;
		}
	}
}

void GameWindow::Update()
{
	Globals::deltaTime = (clock() - lastTime)/1000.0;
	lastTime = clock();
//	Globals::time = clock();
	
	

	//Update MainGame
	mainGame.Update();
	
}

void GameWindow::Render()
{

	//Globals::CAPass::Amount = (glm::sin(clock() / 500.0f) + 1.0f)*10.0f;
	
	//enables
	glEnable(GL_DEPTH_TEST);

	passManager.Bind();

	//Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Render MainGame
	//glBindTexture(GL_TEXTURE_2D, 0);
	mainGame.Render();


	//Depth testing
	glDisable(GL_DEPTH_TEST); 
	
	//PASS RENDERS
	passManager.Render();
	passManager.LastPass();

	

	//Swap Buffer
	SDL_GL_SwapWindow(Globals::gameWindow);
	

	//FPS counter
	fpscounter++;
	if (floor(clock()/1000.0) != fpslastSec)
	{
		cout << "FPS: " << fpscounter << endl;
		fpscounter = 0;
		fpslastSec = floor(clock() / 1000.0);
		cout << "DeltaTime: " << Globals::deltaTime << endl;
		//cout << "Time: " << clock() << endl;
	}

}

void GameWindow::Unload()
{
	mainGame.Unload();
	
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(Globals::gameWindow);
}
