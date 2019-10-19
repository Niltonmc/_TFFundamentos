#include "Agent.h"
#include "ResourceManager.h"


Agent::Agent()
{
}

void Agent::draw(SpriteBacth& spritebatch, int type) {
	static int textureID = 0;
	switch (type){

	case 1:

		textureID = ResourceManager::getTexture("Textures/733.png").id;

		break;
	case 2:
		textureID = ResourceManager::getTexture("Textures/738.png").id;
		break;
	}

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

		Agent::~Agent(){
}
