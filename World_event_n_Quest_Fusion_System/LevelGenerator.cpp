#include "LevelGenerator.h"

void LevelGenerator::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
	unsigned int width = tileData[0].size(); //x
	unsigned int height = tileData.size(); //y
	//Casting reliably with static_cast
	float unit_width = levelWidth / static_cast<float>(width);
	float unit_height = levelHeight / height;

	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			if (tileData[y][x] == 1) {
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(ResourceManager::GetTexture("Tree"), pos, size, 0.0f, glm::vec3(0.8f, 0.8f, 0.7f));
				walls.push_back(obj);
			}
			/*else if (tileData[y][x] > 1) {
				glm::vec3 color = glm::vec3(1.0f);

				switch (tileData[y][x]) {
				case 2: color = glm::vec3(0.2f, 0.6f, 1.0f);
					break;
				case 3: color = glm::vec3(0.1f, 0.7f, 0.2f);
					break;
				case 4: color = glm::vec3(0.4f, 0.8f, 0.8f);
					break;
				case 5: color = glm::vec3(0.4f, 0.3f, 0.0f);
					break;
				default: std::cout << "Wrong tile code" << std::endl;
				}

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(ResourceManager::GetTexture("Tree"), pos, size, 0.0f, color);
				walls.push_back(obj);
			}*/
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
		wall.Draw(renderer);
	}
}
