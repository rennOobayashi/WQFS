#include "WorldEvent.h"

WorldEvent::WorldEvent() 
	: type(0), positionX(0), positionY(0) {}

void WorldEvent::SetUp(int _type, float posX, float posY) {
	type = _type;
	positionX = posX;
	positionY = posY;
}

void WorldEvent::DoEvent() {

}

int WorldEvent::GetType() const {
	return type;
}