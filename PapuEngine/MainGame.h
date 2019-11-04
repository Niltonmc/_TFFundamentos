#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GLS_Program.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera2D.h"
#include <vector>
#include "SpriteBacth.h"
#include "Level.h"
#include "InputManager.h"
#include "Player.h"
#include "Human.h"
#include "SpriteGenerator.h"

enum class GameState
{
	PLAY, EXIT
};


class MainGame
{
private:
	int _witdh;
	int _height;
	float _time;
	Window _window;
	void init();
	void procesInput();
	GLS_Program _program;
	vector<Sprite*> _sprites;
	Camera2D _camera;
	SpriteBacth _spriteBacth;
	InputManager _inputManager;
<<<<<<< Updated upstream
	vector<Level*> levels;
	int currentLevel;
=======
	vector<Bullet> _bullets;
	vector<Level*> _levels;
	vector<Zombie*> _zombies;
	vector<Human*>  _humans;
	Player* _player;
	int _currenLevel;
>>>>>>> Stashed changes
	void initLevel();
	Player* player;
	vector<Human*> humans;
	vector<SpriteGenerator*> allSpritesVector;

public:
	MainGame();
	~MainGame();
	GameState _gameState;
	void initShaders();
	void run();
	void draw();
	void update();
	void HandleInput();
};

