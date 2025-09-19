#ifndef WORLDEVENT_H
#define WORLDEVENT_H

#include <iostream>

// 1.monster
// 2.earthquake
// 3.landslide
// 4.tsunami

class WorldEvent
{
private:
	float position_x, position_y;
	int type;

	void init();
public:
	WorldEvent(int _type, float pos_x, float pos_y);
	~WorldEvent() { }

	void DoEvent();
	std::string getName();
	int getType();
};

#endif