#include "GameObject.h"

GameObject::GameObject()
	:objPosition(0.0f), objSize(0.0f), objRotation(0.0f), objColor(0.0f), objVelocity(0.0f), flipX(false), flipY(false) { }

GameObject::GameObject(Texture sprite, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec3 color, glm::vec2 velocity)
	: objSprite(sprite), objPosition(pos), objSize(size), objRotation(rotation), objColor(color), objVelocity(velocity), flipX(false), flipY(false) {
}

GameObject::~GameObject() {}

void GameObject::Draw(SpriteRenderer &spriteRenderer, bool isSprite) {
	glm::vec2 objSize = this->objSize;
	glm::vec2 objPosition = this->objPosition;

	if (flipX) {
		objSize.x = -objSize.x;
		objPosition.x += this->objSize.x;
	}
	if (flipY) {
		objSize.y = -objSize.y;
		objPosition.y += this->objSize.y;
	}

	spriteRenderer.DrawSprite(objSprite, objPosition, objSize, objRotation, objColor, isSprite);
}