#pragma once
#ifdef WIN32
#include <Engine/Include/Window.h>
#else
#include <graphics/GraphicsApplication.h>
#endif
#include <Engine/Include/GLSLProgram.h>
#include <Engine/Include/SpriteBatch.h>
#include <Engine/Include/Camera2D.h>
#include <Engine/Include/SpriteFont.h>
#include <Engine/Include/InputManager.h>
#include <Engine/Include/DebugRenderer.h>
#include <Box2D/Box2D.h>
#include "Box.h"
#include "Ship.h"
#include "GATextDemo.h" 
#include "Car.h"
#include "GACar.h"
#include "GAShip.h"
enum GameState
{
	MainMenu, Game, Text, GCar, Exit
};
#ifndef WIN32
class Window;
class GraphicsSystem;
#endif

class MainGame
{
public:
	MainGame();

	~MainGame();

#ifdef WIN32
	void run();
#else
    void run(engine::Window* swindow);
#endif
private:
	int sWidth;
	int sHeight;
	void gLoop();
	void processInput();
	bool initShaders();
	void drawGame();
	void drawHUD();

#ifdef WIN32
	Engine::Window window;
#else
	engine::Window* m_window;
#endif
	GAShip gaShip;
	Engine::GLSLProgram colorP;
	Engine::GLSpriteBatch spriteBatch;
	Engine::GLSpriteBatch spriteBatchTri;
	Engine::GLSpriteBatch UIspriteBatch;
	Engine::SpriteFont* spriteFont;
	Engine::Camera2D cam2D;
	Engine::Camera2D hudCam;
	Engine::InputManager inputManager;
	Engine::DebugRenderer dRender;
	b2World* world;
	Box Ground;
	Car car;
	std::vector<glm::vec4> pos;
	std::vector<glm::vec4*> posP;
	static bool compFrontToBack(glm::vec4* a, glm::vec4* b);
	bool renderDebug = false;
	//Level map;
	Ship ship;
	Box box;
	GameState gMode;
	GameState nMode;
	GATextDemo test;
	GACar Evo;
};

