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
#include "PostProcessing.h"

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
	GAME_WIN,
	GAME_OVER
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

typedef std::tuple<GameObject, float> Monster;
typedef std::tuple<std::vector<GameObject>, bool, bool, bool> QuestObject; //obstacle list, isGenerated type(false = 2, true = 3)
typedef std::pair<glm::vec2, int> Moving; //default position, moveDirection(0 = left, 1 = right, 2 = up, 3 = down)
typedef std::pair<GameObject, float> NPCObject;
typedef std::pair<int, bool> Quest;
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
	std::map<std::string, ParticleGenerator> particleGenerators;
	std::map<std::string, Quest> questList;
	LevelGenerator level;

	glm::mat4 view;
	GameState states;
	Direction playerLastDir;
	unsigned int width, height;
	unsigned int mapWidth, mapHeight;
	float deltaTime;
	float lastFrame;
	float changeMoveTime, showDangerousTime;
	float dangerousDelay, mapLoadingDelay, attackDelay;
	float pauseDelayTimer, pauseDelay;
	float moveAnimationTimer;
	float playerHitDelay;
	int hp, monsterHp;
	int damage;
	bool changedir;
	bool mapLoading, getItemFirstTime, isAttacked;
	bool isMoving;
	bool useWQFS;

	GLFWwindow* window;

	GameObject* player;
	GameObject* attackBox;
	GameObject* questGameObject;
	GameObject* InventoryObject;
	GameObject* hpObjects;

	SpriteRenderer* sRenderer;
	TextRenderer* textRenderer;
	PostProcessing* effects;
	irrklang::ISoundEngine *soundEngine;

	bool stopInput[4];
	Direction stopDir;

	void init();
	void render();
	void ProcessInput(GLFWwindow* window, float dt);
	void MoveSelf(float dt);
	void CameraMove(float dt);
	void DoCollisions();
	void Reset();
	void CheckGameState();
	void MakeQusetObject(int questNumber, glm::vec2 offset);
	bool CheckCollision(GameObject& object1, GameObject& object2);
	bool CheckCollision(glm::vec2 object1Pos, glm::vec2 object1Size, glm::vec2 object2Pos, glm::vec2 object2Size);
	Direction CheckCollisionDirection(GameObject& object1, GameObject& object2, bool isPlayer = true);
public:
	OpenGLCode(unsigned int _width, unsigned int _height);
	~OpenGLCode(); //Destructor
	void update();
};

#endif

