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
	float positionX, positionY, positionZ;
	float sizeX, sizeY, sizeZ;
	int type;
	int hp;
	bool isVisible;
	bool doEvent;
	bool isCanCollid;
	bool isMove;
	clock_t start;
	clock_t eventStart;
	float eventTimer;
	float maxTime;
	float durationTimer;
	float duration;
	float collideDelay;
	float pauseDuration;
	int errorValue;
	int errorTime;
public:
	WorldEvent();
	~WorldEvent() { }

	void SetUp(int _number, int _type, int _hp, float posX, float posY, float sizeX, float sizeY, float _maxTime, float _duration, float _collideDelay, int _errorValue);
	void Timer();
	void ResetTimer();

	void SetPositionX(float x);
	float GetPositionX() const;
	void SetPositionY(float y);
	float GetPositionY() const;
	void SetPositionZ(float z);
	float GetPositionZ() const;
	void SetPosition(float x, float y);
	void SetPosition(float x, float y, float z);
	void SetSizeX(float x);
	float GetSizeX() const;
	void SetSizeY(float y);
	float GetSizeY() const;
	void SetSizeZ(float z);
	float GetSizeZ() const;
	void SetSize(float x, float y);
	void SetSize(float x, float y, float z);
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
	void SetIsCanCollid(bool b);
	bool GetIsCanCollid() const;
	void SetIsMove(bool b);
	bool GetIsMove() const;
	void SetPauseDuration(float duration);
	float GetPauseDuration() const;

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
		this->positionZ = other.positionZ;
		this->sizeX = other.sizeX;
		this->sizeY = other.sizeY;
		this->sizeZ = other.sizeZ;
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
		this->isMove = other.isMove;
		this->errorTime = other.errorTime;
		this->errorValue = other.errorValue;

		return *this;
	}
};

#endif