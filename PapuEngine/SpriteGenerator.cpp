#include "ResourceManager.h"
#include <iostream>
#include "SpriteGenerator.h"

void SpriteGenerator::Init(glm::vec2 _spritePosition, int _spriteType){
	spriteColor.r = 255;
	spriteColor.g = 255;
	spriteColor.b = 255;
	spriteColor.a = 255;
	spriteType = _spriteType;
	spritePosition = _spritePosition;
	InitSpriteVector();
}

void SpriteGenerator::Draw(SpriteBacth& spritebatch){
	static int textureID;
	textureID = ResourceManager::getTexture(allSpriteNames[spriteType]).id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(spritePosition.x, spritePosition.y, SPRITE_WIDTH, SPRITE_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, spriteColor);
}
void SpriteGenerator::InitSpriteVector(){
	allSpriteNames.push_back("Textures/730.png");
	allSpriteNames.push_back("Textures/743.png");
	allSpriteNames.push_back("Textures/748.png");
	allSpriteNames.push_back("Textures/763.png");
	allSpriteNames.push_back("Textures/786.png");
	allSpriteNames.push_back("Textures/788.png");
}