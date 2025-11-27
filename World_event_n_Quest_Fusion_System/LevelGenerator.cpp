#include "LevelGenerator.h"

void LevelGenerator::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
	unsigned int width = tileData[0].size(); //x
	unsigned int height = tileData.size(); //y
	//Casting reliably with static_cast
	float unitWidth = static_cast<float>(levelWidth) / width;
	float unitHeight = static_cast<float>(levelHeight) / height;

	for (auto& event : WQFS::GetInstance().worldEvents) {
		if (event.second.GetSubType() != -1 && event.second.GetType() != 0) {
			events[event.second.GetSubType()] = event.first;
		}
		else if (event.second.GetSubType() != -1 && event.second.GetType() == 0) {
			monsters[event.second.GetSubType()] = event.first;
		}
	}
	for (auto& npc : WQFS::GetInstance().npcs) {
		if (npc.second.GetSubType() != -1) {
			npcs[npc.second.GetSubType()] = npc.first;
		}
	}

	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			GameObject obj;
			glm::vec2 pos(unitWidth * x, unitHeight * y);
			glm::vec2 size(unitWidth, unitHeight);
			switch (tileData[y][x]) {
				case 1: //Route tile
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(190 / 255.0f));
					tiles.push_back(obj);
					break;
				case 2: //Ocean tile
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					tiles.push_back(obj);
					break;
				case 3: //Mountain tile
					obj = GameObject(ResourceManager::GetTexture("MountainTile"), pos, size, 0.0f, glm::vec3(150 / 255.0f));
					walls.push_back(obj);
					break;
				case 4: //Tree tile
					obj = GameObject(ResourceManager::GetTexture("Tree"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 5: //Landslide event Object
					WQFS::GetInstance().GetEvent(events[0]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("MountainTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 6: //Earthquake event Object
					WQFS::GetInstance().GetEvent(events[1]).SetPosition(pos.x, pos.y);
					break;
				case 7: //Tsunami event Object
					WQFS::GetInstance().GetEvent(events[2]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
					break;
				case 8: //Monster Object
					WQFS::GetInstance().GetEvent(monsters[0]).SetPosition(pos.x, pos.y);
					break;
				case 9: //NPC Object
					WQFS::GetInstance().GetNPC(npcs[0]).SetPosition(pos.x, pos.y);
					break;
				case 10: //Tornado event Object
					WQFS::GetInstance().GetEvent(events[3]).SetPosition(pos.x, pos.y);
					break;
				case 21: //Ocean colid tile
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
			}
		}
	}
}

void LevelGenerator::Load(const char* file, unsigned int level_width, unsigned int level_height) {
	//Clear old datas
	walls.clear();
	tiles.clear();

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

bool LevelGenerator::CheckCollision(glm::vec2 object1Pos, glm::vec2 object1Size, glm::vec2 object2Pos, glm::vec2 object2Size) {
	bool collisionX = object1Pos.x + object1Size.x >= object2Pos.x &&
		object2Pos.x + object2Size.x >= object1Pos.x;
	bool collisionY = object1Pos.y + object1Size.y >= object2Pos.y &&
		object2Pos.y + object2Size.y >= object1Pos.y;

	return collisionX && collisionY;
}

void LevelGenerator::Draw(SpriteRenderer& renderer, glm::vec2 cameraPos, glm::vec2 windowSize) {
	for (GameObject& wall : walls) {
		//std::cout << wall.objSize.x << " " << wall.objSize.y << std::endl;
		if (CheckCollision(cameraPos, windowSize, wall.objPosition, wall.objSize)) {
			wall.Draw(renderer, true);
		}
	}

	for (GameObject& tile : tiles) {
		//std::cout << wall.objSize.x << " " << wall.objSize.y << std::endl;
		if (CheckCollision(cameraPos, windowSize, tile.objPosition, tile.objSize)) {
			tile.Draw(renderer, true);
		}
	}
}

void LevelGenerator::Clear() {
	walls.clear();
}