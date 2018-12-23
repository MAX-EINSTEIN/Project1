#pragma once
#include<SDL.h>
#include<glew.h>
#include"Sprite.h"
#include"GLSLPogram.h"
#include"GLTexture.h"

enum GameState{ PLAY,EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	SDL_Window* _window;
	int _screenWidht;
	int _screenHeight;
	
	std::vector <Sprite*> _sprites;

	GLSLPogram _colorProgram;

	GameState _gameState;

	GLTexture _playerTexture;

	float _time;

};

