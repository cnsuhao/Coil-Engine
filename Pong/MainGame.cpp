#include "MainGame.h"

Vertex vertices[3] = {
	Vertex(vec3(0, 1.0, 0),		vec2(0.5, 1.0), vec3(0,0,1.0)),
	Vertex(vec3(1.0, -1.0, 0),	vec2(1.0, 0),	vec3(0,0,1.0)),
	Vertex(vec3(-1.0, -1.0, 0),	vec2(0,0),		vec3(0,0,1.0))
};

Mesh testMesh = Mesh();

Transform testATransform = Transform(
	vec3(0.0),
	vec3(0.0),
	vec3(2.0)
	);

Transform testBTransform = Transform(
	vec3(1.0, 0.0, -0.5),
	vec3(0.0),
	vec3(1.5)
	);

Camera testCamera = Camera(
	vec3(0.0f, 0.0f, -5.0f),
	70.0f,
	(float)Globals::windowWidth / (float)Globals::windowHeight,
	0.1f,
	1000.0f
	);
DerpShader derpShader = DerpShader();
Texture testTexture = Texture();

MainGame::MainGame()
{
}
MainGame::~MainGame()
{
}

void MainGame::Load()
{
	cout << "MainGame loaded." << endl;
	testMesh.Load(vertices, 3);
	testTexture.Load("bricks");
	
	derpShader.Load();
	
}

void MainGame::Update()
{
	//testTransform.SetRot(vec3(0, Globals::time/500.0, 0));
	//testTransform.rot = vec3(0.0, 45.0, 0.0);
	//testATransform.rot = vec3(0.0, clock() / 5, 0.0);
	testBTransform.rot = vec3(0, clock()/100.0, 0);
}

void MainGame::Render()
{
	testTexture.Bind(0);
	
	derpShader.Bind(testATransform, testCamera);
	testMesh.Draw();

	derpShader.Bind(testBTransform, testCamera);
	testMesh.Draw();
}

void MainGame::Unload()
{
	testMesh.Unload();
}
