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

<<<<<<< Updated upstream
void MainGame::initLevel(){
	currentLevel = 0;
	levels.push_back(new Level("Levels/level.txt"));
	player = new Player();
	player->init(1.0f,
		levels[currentLevel]->getPlayerPosition(),
		&_inputManager);
	_spriteBacth.init();
=======
void MainGame::initLevel() {
	_levels.push_back(new Level("Levels/level1.txt"));
	_player = new Player();
	_currenLevel = 0;
	_player->init(1.0f, _levels[_currenLevel]->getPlayerPosition(), &_inputManager,&_camera);
	_humans.push_back(_player);
	_spriteBacth.init();

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int>randPosX(
		1, _levels[_currenLevel]->getWidth()-2);
	std::uniform_int_distribution<int>randPosY(
		1, _levels[_currenLevel]->getHeight()-2);

	for (int i = 0; i < _levels[_currenLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human());
		glm::vec2 pos(randPosX(randomEngine)*TILE_WIDTH, 
							randPosY(randomEngine)*TILE_WIDTH);
		_humans.back()->init(1.0f, pos);
	}

	const std::vector<glm::vec2>& zombiePosition =
		_levels[_currenLevel]->getZombiesPosition();

	for (size_t i = 0; i < zombiePosition.size(); i++)
	{
		_zombies.push_back(new Zombie());
		_zombies.back()->init(1.3f, zombiePosition[i]);
	}
>>>>>>> Stashed changes
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/ColorRGBAShaderVert.txt",
		"Shaders/ColorRGBAShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColorRGBA");
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
<<<<<<< Updated upstream
	levels[currentLevel]->draw();
	player->draw(_spriteBacth);
=======
	_levels[_currenLevel]->draw();
		
	glm::vec2 agentPos;
	glm::vec2 agentDims(AGENT_RADIUS * 2.0f);
	for (size_t i = 0; i < _humans.size(); i++)
	{
		
		if (_camera.isBoxInView(_humans[i]->getPosition(), agentDims)) {
			_humans[i]->draw(_spriteBacth);
		}
		
	}
>>>>>>> Stashed changes

	for (size_t i = 0; i < allSpritesVector.size(); i++){
		allSpritesVector[i]->Draw(_spriteBacth);
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
<<<<<<< Updated upstream

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
=======
		if (_inputManager.isKeyDown(SDLK_q)) {
>>>>>>> Stashed changes
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyDown(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}
<<<<<<< Updated upstream
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords =  _camera.convertScreenToWorl(_inputManager.getMouseCoords());
			cout << mouseCoords.x << " " << mouseCoords.y << endl;
		}*/
=======

>>>>>>> Stashed changes
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		HandleInput();
		draw();
		_camera.update();
		_time += 0.002f;
<<<<<<< Updated upstream
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
=======
		updateAgents();
		_inputManager.update();
		_camera.setPosition(_player->getPosition());
	}
}

void MainGame::updateAgents() {


	for (size_t i = 0; i < _humans.size(); i++)
	{
		
		_humans[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans,_zombies);
>>>>>>> Stashed changes
	}
	if (_inputManager.isKeyPressed(SDLK_j))
	{
<<<<<<< Updated upstream
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
=======
		_zombies[i]->update(_levels[_currenLevel]->getLevelData(),
			_humans, _zombies);


		for (size_t j = 1; j < _humans.size(); j++)
		{
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				_zombies.push_back(new Zombie);
				_zombies.back()->init(1.3f, _humans[j]->getPosition());

				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}
>>>>>>> Stashed changes
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