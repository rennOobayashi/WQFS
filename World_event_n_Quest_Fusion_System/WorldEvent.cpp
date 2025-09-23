#include "WorldEvent.h"

WorldEvent::WorldEvent() 
	: positionX(0), positionY(0) {}

void WorldEvent::SetUp(float posX, float posY) {
	positionX = posX;
	positionY = posY;
}

void WorldEvent::DoEvent() {

}