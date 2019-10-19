#include "Zombie.h"



Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::Init(float _zombieSpeed, glm::vec2 _zombiePosition, int _characterTpye){
	characterType = _characterTpye;
	speed = _zombieSpeed;
	position = _zombiePosition;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

}

void Zombie::update()
{
}
