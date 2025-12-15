#include "LevelGenerator.h"

void LevelGenerator::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
	unsigned int width = tileData[0].size(); //x
	unsigned int height = tileData.size(); //y
	//Casting reliably with static_cast
	float unitWidth = static_cast<float>(levelWidth) / width;
	float unitHeight = static_cast<float>(levelHeight) / height;

	for (auto& event : WQFS::GetInstance().worldEvents) {
		if (event.second.GetSubType() != -1 && event.first.find("Landslide") != std::string::npos && event.second.GetType() != 0) {
			landslideEvents[event.second.GetSubType()] = event.first;
		}
		else if (event.second.GetSubType() != -1 && event.first.find("Earthquake") != std::string::npos && event.second.GetType() != 0) {
			earthquakeEvents[event.second.GetSubType()] = event.first;
		}
		else if (event.second.GetSubType() != -1 && event.first.find("Tsunami") != std::string::npos && event.second.GetType() != 0) {
			tsunamiEvents[event.second.GetSubType()] = event.first;
		}
		else if (event.second.GetSubType() != -1 && event.first.find("Tornado") != std::string::npos && event.second.GetType() != 0) {
			tornadoEvents[event.second.GetSubType()] = event.first;
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
				case 3: //Ocean colid tile
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
					break;
				case 4: //Tree tile
					obj = GameObject(ResourceManager::GetTexture("Tree"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 5: //Mountain tile
					obj = GameObject(ResourceManager::GetTexture("MountainTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 6: //Mountain left tile
					obj = GameObject(ResourceManager::GetTexture("MountainLeftTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 7: //Mountain right tile
					obj = GameObject(ResourceManager::GetTexture("MountainRightTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 8: //Mountain left top tile
					obj = GameObject(ResourceManager::GetTexture("MountainLeftTopTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 9: //Mountain right top tile
					obj = GameObject(ResourceManager::GetTexture("MountainRightTopTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 10: //Mountain top tile
					obj = GameObject(ResourceManager::GetTexture("MountainTopTile"), pos, size, 0.0f, glm::vec3(1.0f));
					walls.push_back(obj);
					break;
				case 11: //Earthquake event Object
					WQFS::GetInstance().GetEvent(earthquakeEvents[0]).SetPosition(pos.x, pos.y);
					break;
				case 12: //Earthquake event Object
					WQFS::GetInstance().GetEvent(earthquakeEvents[1]).SetPosition(pos.x, pos.y);
					break;
				case 13: //Earthquake event Object
					WQFS::GetInstance().GetEvent(earthquakeEvents[2]).SetPosition(pos.x, pos.y);
					break;
				case 14: //Landslide event Object
					WQFS::GetInstance().GetEvent(landslideEvents[0]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("MountainTile"), pos, size, 0.0f, glm::vec3(1.0f));
					tiles.push_back(obj);
					//walls.push_back(obj);
					break;
				case 15: //Landslide event Object
					WQFS::GetInstance().GetEvent(landslideEvents[1]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("MountainTile"), pos, size, 0.0f, glm::vec3(1.0f));
					tiles.push_back(obj);
					//walls.push_back(obj);
					break;
				case 16: //Tsunami event Object
					WQFS::GetInstance().GetEvent(tsunamiEvents[0]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
					break;
				case 17: //Tsunami event Object
					WQFS::GetInstance().GetEvent(tsunamiEvents[1]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
					break;
				case 18: //Tsunami event Object
					WQFS::GetInstance().GetEvent(tsunamiEvents[2]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
					break;
				case 19: //Tsunami event Object
					WQFS::GetInstance().GetEvent(tsunamiEvents[3]).SetPosition(pos.x, pos.y);
					obj = GameObject(ResourceManager::GetTexture("GroundTile"), pos, size, 0.0f, glm::vec3(200 / 255.0f));
					walls.push_back(obj);
					break;
				case 20: //Tornado event Object
					WQFS::GetInstance().GetEvent(tornadoEvents[0]).SetPosition(pos.x, pos.y);
					break;
				case 21: //Tornado event Object
					WQFS::GetInstance().GetEvent(tornadoEvents[1]).SetPosition(pos.x, pos.y);
					break;
				case 22: //Tornado event Object
					WQFS::GetInstance().GetEvent(tornadoEvents[2]).SetPosition(pos.x, pos.y);
					break;
				case 23: //Monster Object
					WQFS::GetInstance().GetEvent(monsters[0]).SetPosition(pos.x, pos.y);
					break;
				case 24: //Monster Object
					WQFS::GetInstance().GetEvent(monsters[1]).SetPosition(pos.x, pos.y);
					break;
				case 25: //Monster Object
					WQFS::GetInstance().GetEvent(monsters[2]).SetPosition(pos.x, pos.y);
					break;
				case 26: //NPC Object
					WQFS::GetInstance().GetNPC(npcs[0]).SetPosition(pos.x, pos.y);
					break;
				case 27: //NPC Object
					WQFS::GetInstance().GetNPC(npcs[1]).SetPosition(pos.x, pos.y);
					break;
				case 28: //NPC Object
					WQFS::GetInstance().GetNPC(npcs[2]).SetPosition(pos.x, pos.y);
					break;
				case 29: //NPC Object
					WQFS::GetInstance().GetNPC(npcs[3]).SetPosition(pos.x, pos.y);
					break;
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