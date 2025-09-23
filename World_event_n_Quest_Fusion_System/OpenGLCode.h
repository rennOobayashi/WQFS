#ifndef OPENGLCODE_H
#define	OPENGLCODE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

enum GameState {
	GAME_ACTIVE, //0
	GAME_MENU,   //1
	GAME_WIN     //2
};


class OpenGLCode
{
private:
	std::vector<GameObject> npcObjects;
	std::vector<GameObject> monsterObjects;
	std::vector<GameObject> eventObjects;

	GameState states;
	unsigned int width, height;
	float deltaTime;
	float lastFrame;
	float changeMoveTime;
	bool changedir;

	GLFWwindow* window;
	SpriteRenderer* sRenderer;



	void init();
	void render();
	void MoveSelf(float dt);
	void CheckCollision();
public:
	OpenGLCode(unsigned int _width, unsigned int _height);
	~OpenGLCode(); //Destructor
	void update();
};

#endif

