#ifndef WORLDEVENT_H
#define WORLDEVENT_H

#include <iostream>

// Default world event types:
// 0. monster
// 1. static
// 2. dynamic

class WorldEvent
{
private:
	int number;
	int questNumber;
	float positionX, positionY;
	int type;
	int hp;
	bool isVisible;

	void init();
public:
	WorldEvent();
	~WorldEvent() { }

	void SetUp(int _number, int _type, int _hp, float posX, float posY);
	void DoEvent();

	void SetPositionX(float x);
	float GetPositionX() const;
	void SetPositionY(float y);
	float GetPositionY() const;
	void SetPosition(float x, float y);
	int GetType() const;
	void setQuestNumber(int n);
	int getQuestNumber() const;
	void setHp(int _hp);
	int getHp() const;
	void takeDamage(int damage);
	void setVisible(bool b);
	bool getVisible() const;

	bool operator<(const WorldEvent& other) const {
		return type < other.type;
	};

	bool operator==(const WorldEvent& other) const {
		return this->number == other.number;
	}

	WorldEvent& operator=(const WorldEvent& other) {
		if (this == &other) {
			return *this;
		}

		this->number = other.number;
		this->questNumber = other.questNumber;
		this->positionX = other.positionX;
		this->positionY = other.positionY;
		this->type = other.type;
		this->hp = other.hp;
		this->isVisible = other.isVisible;

		return *this;
	}
};

#endif