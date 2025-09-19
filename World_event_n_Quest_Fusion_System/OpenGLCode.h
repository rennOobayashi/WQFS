#ifndef OPENGLCODE_H
#define	OPENGLCODE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

enum GameState {
	GAME_ACTIVE, //0
	GAME_MENU,   //1
	GAME_WIN     //2
};


class OpenGLCode
{
private:
	GameState states;
	unsigned int width, height;
	float delta_time;
	float last_frame;

	GLFWwindow* window;

	void init();
public:
	OpenGLCode(unsigned int _width, unsigned int _height);
	~OpenGLCode(); //Destructor
	void update();
};

#endif

