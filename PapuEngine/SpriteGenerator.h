#pragma once
#include <glm/glm.hpp>
#include "SpriteBacth.h"
#include "GLTexture.h"
#include<vector>
#include<string>
using namespace std;

const int  SPRITE_WIDTH = 60.f;
const int  SPRITE_RADIUS = SPRITE_WIDTH / 2.0f;

class SpriteGenerator{
private:
	glm::vec2 spritePosition;
	int spriteType;
	Color spriteColor;
	vector <string> allSpriteNames;

public:
	glm::vec2 GetPosition() {
		return spritePosition;
	}
	void Init(glm::vec2 _spritePosition, int _spriteType);
	void Draw(SpriteBacth& spritebatch);
	void InitSpriteVector();
};
