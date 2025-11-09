#ifndef WORLDEVENT_H
#define WORLDEVENT_H

#include <Windows.h>
#include <time.h>
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
	float sizeX, sizeY;
	int type;
	int hp;
	bool isVisible;
	bool doEvent;
	bool isCanCollid;
	clock_t start;
	clock_t eventStart;
	double eventTimer;
	double maxTime;
	double durationTimer;
	double duration;
	double collideDelay;
	double pauseDuration;
public:
	WorldEvent();
	~WorldEvent() { }

	void SetUp(int _number, int _type, int _hp, float posX, float posY, float sizeX, float sizeY, double _maxTime, double _duration, double _collideDelay);
	void Timer();
	void ResetTimer();

	void SetPositionX(float x);
	float GetPositionX() const;
	void SetPositionY(float y);
	float GetPositionY() const;
	void SetPosition(float x, float y);
	void SetSizeX(float x);
	float GetSizeX() const;
	void SetSizeY(float y);
	float GetSizeY() const;
	void SetSize(float x, float y);
	int GetType() const;
	void setQuestNumber(int n);
	int getQuestNumber() const;
	void setHp(int _hp);
	int getHp() const;
	void takeDamage(int damage);
	void setVisible(bool b);
	bool getVisible() const;
	void setDoEvent(bool b);
	bool getDoEvent() const;
	void GetIsCanCollid(bool b);
	bool GetIsCanCollid() const;
	void SetPauseDuration(double duration);
	double GetPauseDuration() const;

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
		this->sizeX = other.sizeX;
		this->sizeY = other.sizeY;
		this->type = other.type;
		this->hp = other.hp;
		this->isVisible = other.isVisible;
		this->start = other.start;
		this->eventTimer = other.eventTimer;
		this->maxTime = other.maxTime;
		this->durationTimer = other.durationTimer;
		this->duration = other.duration;
		this->doEvent = other.doEvent;
		this->collideDelay = other.collideDelay;
		this->isCanCollid = other.isCanCollid;
		this->pauseDuration = other.pauseDuration;

		return *this;
	}
};

#endif