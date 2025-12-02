#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "spriterenderer.h"
#include "gameobject.h"
#include "resourcemanager.h"
#include "WQFS.h"


class LevelGenerator
{
private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
	bool CheckCollision(glm::vec2 object1Pos, glm::vec2 object1Size, glm::vec2 object2Pos, glm::vec2 object2Size);
public:
	std::vector<GameObject> tiles;
	std::vector<GameObject> walls; //Collision objects
	std::map<int, std::string> landslideEvents; // eventSubType(id), name
	std::map<int, std::string> earthquakeEvents; // eventSubType(id), name
	std::map<int, std::string> tsunamiEvents; // eventSubType(id), name
	std::map<int, std::string> tornadoEvents; // eventSubType(id), name
	std::map<int, std::string> monsters; // eventSubType(id), name
	std::map<int, std::string> npcs;

	LevelGenerator() {}
	void Load(const char* file, unsigned int level_width, unsigned int level_height);
	void Draw(SpriteRenderer& renderer, glm::vec2 cameraPos, glm::vec2 windowSize);
	void Clear();
};

#endif