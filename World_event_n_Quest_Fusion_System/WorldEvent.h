#ifndef WORLDEVENT_H
#define WORLDEVENT_H

#include <iostream>

// Example world event types:
// 0. monster
// 1. static
// 2. dynamic

class WorldEvent
{
private:
	int type;

	void init();
public:
	float positionX, positionY;
	WorldEvent();
	~WorldEvent() { }

	void SetUp(int _type, float posX, float posY);
	void DoEvent();
	int GetType() const;

	bool operator<(const WorldEvent& other) const {
		return type < other.type;
	};
};

#endif