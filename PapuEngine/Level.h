#pragma once
#include <string>
#include <vector>
#include "SpriteBacth.h"


using namespace std;

const int TILE_WIDTH = 64;

class Level
{
private:
	vector<string> levelData;
	int numHumans;
	void parseLevel();
public:
<<<<<<< Updated upstream
	Level(const string& filename);
	glm::vec2 playerPosition;
	vector<glm::vec2> zombiesPosition;
	glm::vec2 getPlayerPosition() const {
		return playerPosition;
	}
	vector<glm::vec2> getZombiesPosition()const {
		return zombiesPosition;
	}
=======
	glm::vec2 _playerPosition;
	std::vector<glm::vec2> _zombiesPosition;
	glm::vec2 getPlayerPosition() const { 
		return _playerPosition; 
	};
	std::vector<glm::vec2> getZombiesPosition()const {
		return _zombiesPosition;
	};

	int getNumHumans() const{
		return _numHumans;
	};

	int getWidth() const {
		return _levelData[0].size();
	};

	int getHeight() const {
		return _levelData[0].size();
	};

	std::vector<string> getLevelData() const{
		return _levelData;
	};

	Level(const std::string& fileName);
>>>>>>> Stashed changes
	void draw();
	SpriteBacth spritebatch;
	int GetWidth();
	int GetHeight();
	~Level();
};

