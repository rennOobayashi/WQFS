#ifndef OPENGLCODE_H
#define	OPENGLCODE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "WQFS.h"

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

class OpenGLCode
{
private:
	std::map<std::string, GameObject > npcObjects;
	std::map<std::string, GameObject> monsterObjects;
	std::map<std::string, GameObject> eventObjects;

	glm::mat4 view;
	GameState states;
	unsigned int width, height;
	unsigned int cameraX, cameraY;
	float deltaTime;
	float lastFrame;
	float changeMoveTime;
	float resetTimer;
	bool changedir;
	bool startResetTimer;
	bool mapLoading, getItemFirstTime;

	GLFWwindow* window;
	SpriteRenderer* sRenderer;


	GameObject* player;


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

