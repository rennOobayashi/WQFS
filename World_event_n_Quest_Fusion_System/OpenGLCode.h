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
#include "LevelGenerator.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <irrKlang.h>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

enum GameState {
	GAME_ACTIVE, 
	GAME_MAIN_MENU,
	GAME_MENU, 
	GAME_WIN  
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef std::tuple<GameObject, int> Monster;
typedef std::tuple<std::vector<GameObject>, bool, bool, bool> QuestObject; //obstacle list, isGenerated type(false = 2, true = 3)
typedef std::pair<glm::vec2, int> Moving; //default position, moveDirection(0 = left, 1 = right, 2 = up, 3 = down)
typedef std::pair<GameObject, float> NPCObject;

class OpenGLCode
{
private:
	std::map<std::string, NPCObject> npcObjects;
	std::map<std::string, Monster> monsterObjects;
	std::map<std::string, GameObject> eventObjects;
	std::map<int, GameObject> questObjects; //quest number, object
	std::map<Item, int> inventory; //Item, count
	std::map<std::string, glm::vec3> defaultColors;
	std::map<std::string, Moving> defaultPosition;
	std::map<int, QuestObject> QuestObjects;
	std::map<std::string, GameObject> itemObjects;
	std::vector<std::string> landslide;
	std::vector<std::string> tornado;
	LevelGenerator level;

	glm::mat4 view;
	GameState states;
	unsigned int width, height;
	unsigned int mapWidth, mapHeight;
	float deltaTime;
	float lastFrame;
	float changeMoveTime, showDangerousTime;
	float dangerousDelay, mapLoadingDelay, attackDelay;
	float pauseDelayTimer, pauseDelay;
	float moveAnimationTimer;
	int hp, monsterHp;
	bool changedir;
	bool mapLoading, getItemFirstTime, isAttacked;
	bool isMoving;

	GLFWwindow* window;
	SpriteRenderer* sRenderer;

	GameObject* player;
	GameObject* attackBox;
	GameObject* questGameObject;
	GameObject* InventoryObject;
	GameObject* hpObjects;

	TextRenderer* textRenderer;

	ParticleGenerator* particleGenerator;

	irrklang::ISoundEngine *soundEngine;

	void init();
	void render();
	void ProcessInput(GLFWwindow* window, float dt);
	void MoveSelf(float dt);
	void CameraMove(float dt);
	void DoCollisions();
	void Reset();
	void MakeQusetObject(int questNumber, glm::vec2 offset);
	bool CheckCollision(GameObject& object1, GameObject& object2);
	bool CheckCollision(glm::vec2 object1Pos, glm::vec2 object1Size, glm::vec2 object2Pos, glm::vec2 object2Size);
public:
	OpenGLCode(unsigned int _width, unsigned int _height);
	~OpenGLCode(); //Destructor
	void update();
};

#endif

