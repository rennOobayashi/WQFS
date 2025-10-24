#include "WorldEvent.h"

WorldEvent::WorldEvent() 
	: number(-1), type(-1), hp(-1), positionX(0), positionY(0), questNumber(-1), isVisible(true) { }

void WorldEvent::SetUp(int _number, int _type, int _hp, float posX, float posY) {
	number = _number;
	type = _type;
	if (type == 0) {
		hp = _hp;
	}
	std::cout << type << " " << hp << std::endl;
	positionX = posX;
	positionY = posY;
}

void WorldEvent::DoEvent() {

}

int WorldEvent::GetType() const {
	return type;
}

void WorldEvent::SetPositionX(float x) {
	positionX = x;
}

float WorldEvent::GetPositionX() const {
	return positionX;
}

void WorldEvent::SetPositionY(float y) {
	positionY = y;
}

float WorldEvent::GetPositionY() const {
	return positionY;
}

void WorldEvent::SetPosition(float x, float y) {
	positionX = x;
	positionY = y;
}

void WorldEvent::setQuestNumber(int n) {
	questNumber = n;
}

int WorldEvent::getQuestNumber() const {
	return questNumber;
}

void WorldEvent::setHp(int _hp) {
	if (_hp < 0) {
		hp = 0;
	}
	else {
		hp = _hp;
	}
}

int WorldEvent::getHp() const {
	return hp;
}

void WorldEvent::takeDamage(int damage) {
	if (type == 0) {
		hp -= damage;
		if (hp < 0) {
			hp = 0;
		}
	}

	std::cout << hp << std::endl;
}

void WorldEvent::setVisible(bool b) {
	isVisible = b;
}

bool WorldEvent::getVisible() const {
	return isVisible;
}