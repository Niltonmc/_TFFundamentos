#pragma once
#include"Human.h"
#include<glm/glm.hpp>
class Zombie: public Human {
private:
	int characterType;
public:
	Zombie();
	~Zombie();
	void Init(float _zombieSpeed, glm::vec2 _zombiePosition, int _characterTpye);
	void update();
};

