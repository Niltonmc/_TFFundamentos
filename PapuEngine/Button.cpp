#include "Button.h"
#include "ResourceManager.h"
#include <iostream>


Button::Button(std::string _texture) :
		texture(_texture)
{
	position = glm::vec2(400, 300);
	textureID = ResourceManager::getTexture(texture).id;
}

void Button::draw(SpriteBacth& spritebatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA color;
	color.set(255, 255, 255, 255);
	glm::vec4 destRect(position.x, position.y, 190, 50);
	spritebatch.draw(destRect, uvRect, 
						textureID, 0.0f, color);
}

bool Button::clicked(glm::vec2 _position) {
	return (_position.x > position.x)
		&& (_position.x < position.x  + 190)
		&& (500 - _position.y > position.y)
		&& (500 -_position.y < position.y + 50 );
}


Button::~Button()
{
}
