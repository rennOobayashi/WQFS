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
	float positionX, positionY;
	int type;

	void init();
public:
	WorldEvent();
	~WorldEvent() { }

	void SetUp(int _type, float posX, float posY);
	void DoEvent();

	void SetPositionX(float x);
	float GetPositionX() const;
	void SetPositionY(float y);
	float GetPositionY() const;
	void SetPosition(float x, float y);
	int GetType() const;

	bool operator<(const WorldEvent& other) const {
		return type < other.type;
	};
};

#endif