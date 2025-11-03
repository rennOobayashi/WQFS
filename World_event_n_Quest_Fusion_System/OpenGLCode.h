#ifndef OPENGLCODE_H
#define	OPENGLCODE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "WQFS.h"
#include "TextRenderer.h"
#include "ParticleGenerator.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

enum GameState {
	GAME_ACTIVE, //0
	GAME_MENU,   //1
	GAME_WIN     //2
};

enum Direction {
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef std::tuple<GameObject, float> Monster;

class OpenGLCode
{
private:
	std::map<std::string, GameObject > npcObjects;
	std::map<std::string, Monster> monsterObjects;
	std::map<std::string, GameObject> eventObjects;
	std::map<int, GameObject> questObjects; //quest number, object
	std::map<Item, int> inventory; //Item, count
	std::map<std::string, glm::vec3> defaultColors;

	glm::mat4 view;
	GameState states;
	unsigned int width, height;
	unsigned int mapWidth, mapHeight;
	float deltaTime;
	float lastFrame;
	float changeMoveTime, showDangerousTime;
	float dangerousDelay, mapLoadingDelay, attackDelay;
	int hp;
	bool changedir;
	bool mapLoading, getItemFirstTime, isAttacked;

	GLFWwindow* window;
	SpriteRenderer* sRenderer;

	GameObject* player;
	GameObject* attackBox;

	TextRenderer* textRenderer;

	ParticleGenerator* particleGenerator;

	void init();
	void render();
	void ProcessInput(GLFWwindow* window, float dt);
	void MoveSelf(float dt);
	void CameraMove(float dt);
	void DoCollisions();
	void Reset();
	bool CheckCollision(GameObject& object1, GameObject& object2);
public:
	OpenGLCode(unsigned int _width, unsigned int _height);
	~OpenGLCode(); //Destructor
	void update();
};

#endif

