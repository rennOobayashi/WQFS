#ifndef NPC_H
#define NPC_H

#include <Windows.h>
#include <time.h>
#include <iostream>

// Example NPC types:
// 0. normal
// 1. Item 
// 2. weapon 
// 3. all

class NPC
{
private:
	int number;
	int questNumber;
	float positionX, positionY, positionZ;
	float sizeX, sizeY, sizeZ;
	bool inDangerous;
	bool canDangerous;
	int type, subType;
	clock_t start;
	float timer;
	float maxTime;
	float pauseDuration;
public:
	NPC();
	~NPC() { }

	void SetUp(int _number, int _type, float posX, float posY, float _sizeX, float _sizeY, double _maxTime);
	void SetUp(int _number, int _type, int _subType, float posX, float posY, float _sizeX, float _sizeY, double _maxTime);
	void Timer();
	void ResetTimer();
	int GetType() const;
	int GetSubType() const;

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
	void SetInDangerous(bool _inDangerous);
	bool GetInDangerous() const;
	void SetCanDangerous(bool _canDangerous);
	bool GetCanDangerous() const;
	void setQuestNumber(int n);
	int getQuestNumber() const;
	void SetPauseDuration(float duration);
	float GetPauseDuration() const;

	bool operator<(const NPC& other) const {
		return this->number < other.number;
	}

	bool operator==(const NPC& other) const {
		return this->number == other.number;
	}

	NPC& operator=(const NPC& other) {
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
		this->inDangerous = other.inDangerous;
		this->canDangerous = other.canDangerous;
		this->type = other.type;
		this->start = other.start;
		this->timer = other.timer;
		this->maxTime = other.maxTime;
		this->pauseDuration = other.pauseDuration;
		this->subType = other.subType;

		return *this;
	}
};

#endif