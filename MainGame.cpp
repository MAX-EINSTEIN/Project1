#include "MainGame.h"
#include"Sprite.h"
#include"Error.h"
#include"ImageLoader.h"
#include<cmath>




MainGame::MainGame()
{
	_window = nullptr;
	_screenWidht = 1366;
	_screenHeight = 728;
	_gameState = GameState::PLAY;
	_time = 0.0;
}


MainGame::~MainGame()
{
	SDL_Quit();
}

void MainGame::run()
{
	initSystems();
	_sprites.push_back(new Sprite());
	_sprites.back()->init(-1.0f,-1.0f,1.0f,1.0f, "Textures/MySpecialCharacter.png");

	_sprites.push_back(new Sprite());
	_sprites.back()->init(0.0f, 0.0f, 1.0f, 1.0f, "Textures/MySpecialCharacter.png");

	

	
	//_playerTexture = ImageLoader::loadPNG("Textures/MySpecialCharacter.png");
	gameLoop();
}

void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidht, _screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (_window == nullptr) {
		fatalError("\nSDL Window cannot be created !!!\n");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) fatalError("\nGLContext could not be created !!!\n");

	GLenum error = glewInit();
	if (error != GLEW_OK) fatalError("\nCannot Initialize Glew components !!!\n");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(1.0f, 0.2f, 1.0f, 1.0f);

	initShaders();

}

void MainGame::initShaders()
{
	_colorProgram.compileShaders("Shaders/colorShading.vert.txt", "Shaders/colorShading.frag.txt");
	_colorProgram.addAttributes("vertexPosition");
	_colorProgram.addAttributes("vertexColor");
	_colorProgram.addAttributes("vertexUV");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState == GameState::PLAY) {
		processInput();
		_time += 0.001;
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT: _gameState = GameState::EXIT;
			break;
		}
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	glActiveTexture(GL_TEXTURE0);
	

	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	glUniform1f(textureLocation, 0);

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _time);


	_sprites[0]->draw();
	_sprites[1]->draw();




	_colorProgram.unuse();


	SDL_GL_SwapWindow(_window);
}
