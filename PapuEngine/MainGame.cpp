#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include "ResourceManager.h"
#include "PapuEngine.h"
#include <random>
#include <ctime>

using namespace std;

void MainGame::run() {
	init();
	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Ella se fue :'v", _witdh, _height, 0);
	initLevel();
	initShaders();
}

void MainGame::initLevel(){
	currentLevel = 0;
	levels.push_back(new Level("Levels/level.txt"));
	player = new Player();
	player->init(1.0f,
		levels[currentLevel]->getPlayerPosition(),
		&_inputManager);
	for (size_t i = 0; i < levels[currentLevel]->getZombiesPosition().size(); i++) {
		allZombiesVector.push_back(new Zombie());
		allZombiesVector.back()->Init(0.2f, levels[currentLevel]->getZombiesPosition()[i], 6);
	}
	_spriteBacth.init();
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}


void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1,GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);

	_spriteBacth.begin();
	levels[currentLevel]->draw();
	player->draw(_spriteBacth,1);

	for (size_t i = 0; i < allSpritesVector.size(); i++){
		allSpritesVector[i]->Draw(_spriteBacth);
	}

	for (size_t i = 0; i < allZombiesVector.size(); i++){
		allZombiesVector[i]->draw(_spriteBacth, 2);
	}

	_spriteBacth.end();
	_spriteBacth.renderBatch();
	
	glBindTexture(GL_TEXTURE_2D, 0);

	_program.unuse();
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	const float CAMERA_SPEED = 20.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.setMouseCoords(event.motion.x,event.motion.y);
			break;
			case  SDL_KEYUP:
				_inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				_inputManager.pressKey(event.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(event.button.button);
				break;
		}

		/*if (_inputManager.isKeyPressed(SDLK_w)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			_camera.setPosition(_camera.getPosition() - glm::vec2(0.0, CAMERA_SPEED));
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			_camera.setPosition(_camera.getPosition() - glm::vec2(CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
		}
		if (_inputManager.isKeyPressed(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			cout << mouseCoords.x << " " << mouseCoords.y << endl;
		}*/
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		HandleInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_camera.setPosition(player->getPosition());
		player->update();
	}
}

void MainGame::HandleInput(){
	const float CAMERA_SPEED = 0.02;
	const float SCALE_SPEED = 0.001f;

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(1, levels[currentLevel]->GetWidth() - 2);
	std::uniform_int_distribution<int> randomY(1, levels[currentLevel]->GetHeight() - 2);

	if (_inputManager.isKeyPressed(SDLK_g)){
		allSpritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,
			randomY(randomEngine) * TILE_WIDTH);
		allSpritesVector.back()->Init(pos, 0);
	}
	if (_inputManager.isKeyPressed(SDLK_h))
	{
		allSpritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,
			randomY(randomEngine) * TILE_WIDTH);
		allSpritesVector.back()->Init(pos, 1);
	}
	if (_inputManager.isKeyPressed(SDLK_j))
	{
		allSpritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,
			randomY(randomEngine) * TILE_WIDTH);
		allSpritesVector.back()->Init(pos, 2);
	}
	if (_inputManager.isKeyPressed(SDLK_k))
	{
		allSpritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,
			randomY(randomEngine) * TILE_WIDTH);
		allSpritesVector.back()->Init(pos, 3);
	}
	if (_inputManager.isKeyPressed(SDLK_l))
	{
		allSpritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,
			randomY(randomEngine) * TILE_WIDTH);
		allSpritesVector.back()->Init(pos, 4);
	}
	if (_inputManager.isKeyPressed(SDLK_p))
	{
		allSpritesVector.push_back(new SpriteGenerator());
		glm::vec2 pos(randomX(randomEngine) * TILE_WIDTH,
			randomY(randomEngine) * TILE_WIDTH);
		allSpritesVector.back()->Init(pos, 5);
	}
	if (_inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}
}

MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}