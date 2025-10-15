#ifndef NPC_H
#define NPC_H

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
	float positionX, positionY;
	bool inDangerous;
	int type;
public:
	NPC();
	~NPC() { }

	void SetUp(int _number, int _type, float pos_x, float pos_y);
	int GetType() const;

	void SetPositionX(float x);
	float GetPositionX() const;
	void SetPositionY(float y);
	float GetPositionY() const;
	void SetPosition(float x, float y);
	void SetInDangerous(bool _inDangerous);
	bool GetInDangerous() const;
	void setQuestNumber(int n);
	int getQuestNumber() const;

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
		this->inDangerous = other.inDangerous;
		this->type = other.type;

		return *this;
	}
};

#endif