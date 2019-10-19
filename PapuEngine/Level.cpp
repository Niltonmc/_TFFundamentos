#include "Level.h"
#include <fstream>
#include "Error.h"
#include "ResourceManager.h"

Level::Level(const string& filename)
{
	ifstream file;
	file.open(filename);
	if (file.fail()) {
		fatalError("fallo el archivo " + filename + " GAAAA");
	}
	string tmp;
	file >> tmp >> numHumans;
	while (getline(file, tmp)) {
		levelData.push_back(tmp);
	}
	parseLevel();
}

void Level::draw() {
	spritebatch.renderBatch();
}

int Level::GetWidth()
{
	return TILE_WIDTH;
}

int Level::GetHeight()
{
	return TILE_WIDTH;
}

void Level::parseLevel() {
	spritebatch.init();
	spritebatch.begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	for (size_t y = 0; y < levelData.size(); y++)
	{
		for (size_t x = 0; x < levelData[y].size(); x++)
		{
			char tile = levelData[y][x];
			glm::vec4 desctRect(x*TILE_WIDTH, y*TILE_WIDTH, 
									TILE_WIDTH, TILE_WIDTH);
			switch (tile)
			{
			case 'R':
			case 'G':
			case 'L':
			case 'B':
				spritebatch.draw(desctRect, uvRect,
					ResourceManager::getTexture
						("Textures/red_bricks.png").id,
					0.0f,
					color
					);
				break;
			case '@':
				levelData[y][x] = '.';
				playerPosition.x = x*TILE_WIDTH;
				playerPosition.y = y * TILE_WIDTH;

				break;
			case 'Z':
				break;
			case '.':
				break;
			default: 
				break;
			}
		}
	}
	spritebatch.end();
}


Level::~Level()
{
}
