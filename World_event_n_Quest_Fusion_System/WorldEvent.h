#ifndef WORLDEVENT_H
#define WORLDEVENT_H

#include <iostream>

// Example world event types:
// 1.monster
// 2.earthquake
// 3.landslide
// 4.tsunami

class WorldEvent
{
private:
	float positionX, positionY;

	void init();
public:
	WorldEvent();
	~WorldEvent() { }

	void SetUp(float posX, float posY);
	void DoEvent();
};

#endif