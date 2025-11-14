#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "spriterenderer.h"
#include "gameobject.h"
#include "resourcemanager.h"

class LevelGenerator
{
private:
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
public:
	std::vector<GameObject> walls;

	LevelGenerator() {}
	void Load(const char* file, unsigned int level_width, unsigned int level_height);
	void Draw(SpriteRenderer& renderer);
};

#endif