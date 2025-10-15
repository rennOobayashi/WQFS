#include "GameObject.h"

GameObject::GameObject()
	:objPosition(0.0f), objSize(0.0f), objRotation(0.0f), objColor(0.0f), objVelocity(0.0f) { }

GameObject::GameObject(Texture sprite, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec3 color, glm::vec2 velocity)
	: objSprite(sprite), objPosition(pos), objSize(size), objRotation(rotation), objColor(color), objVelocity(velocity) {
}

GameObject::~GameObject() {}

void GameObject::Draw(SpriteRenderer &spriteRenderer, bool isSprite) {
	spriteRenderer.DrawSprite(objSprite, objPosition, objSize, objRotation, objColor, isSprite);
}