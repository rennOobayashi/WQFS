#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Texture.h"
#include "SpriteRenderer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

class GameObject
{
public:
	glm::vec2 objPosition, objSize, objVelocity;
	glm::vec3 objColor;
	float objRotation;
	Texture objSprite;

	GameObject();
	GameObject(Texture sprite, glm::vec2 pos, glm::vec2 size, float rotation = 0, glm::vec3 color = glm::vec3(0.0f), glm::vec2 velocity = glm::vec2(0.0f));
	~GameObject();

	virtual void Draw(SpriteRenderer &spriteRenderer, bool isSprite = false);
};

#endif