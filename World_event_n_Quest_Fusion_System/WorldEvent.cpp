#include "WorldEvent.h"

WorldEvent::WorldEvent() 
	: number(0), type(0), positionX(0), positionY(0) {}

void WorldEvent::SetUp(int _number, int _type, float posX, float posY) {
	number = _number;
	type = _type;
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