#include "LevelGenerator.h"

void LevelGenerator::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
	unsigned int width = tileData[0].size(); //x
	unsigned int height = tileData.size(); //y
	//Casting reliably with static_cast
	float unitWidth = levelWidth / static_cast<float>(width);
	float unitHeight = levelHeight / height;

	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			GameObject obj;
			glm::vec2 pos(unitWidth * x, unitHeight * y);
			glm::vec2 size(unitWidth, unitHeight);
			switch (tileData[y][x]) {
				case 1: //Route tile
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					break;
				case 2: //Ocean tile
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(185 / 255.0f));
					break;
				case 3: //Tree tile
					obj = GameObject(ResourceManager::GetTexture("Tree"), pos, size, 0.0f, glm::vec3(1.0f));
					break;
			}

			walls.push_back(obj);
		}
	}
}

void LevelGenerator::Load(const char* file, unsigned int level_width, unsigned int level_height) {
	//Clear old datas
	walls.clear();

	//Load from file
	unsigned int tile_code;
	LevelGenerator level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tile_data;

	//File processing
	if (fstream) {
		//Read one line at a time from the level file.
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;

			//Read it separated by spaces.
			while (sstream >> tile_code) {
				row.push_back(tile_code);
			}
			tile_data.push_back(row);
		}

		if (tile_data.size() > 0) {
			init(tile_data, level_width, level_height);
		}
	}
}

void LevelGenerator::Draw(SpriteRenderer& renderer) {
	for (GameObject& wall : walls) {
		wall.Draw(renderer, true);
	}
}
