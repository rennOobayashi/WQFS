#ifndef NPC_H
#define NPC_H

#include <iostream>

// Example NPC types:
// 1. normal
// 2. Item 
// 3. weapon 
// 4. all

class NPC
{
private:
	float positionX, positionY;
	bool inDangerous;
	int type;
public:
	NPC();
	~NPC() { }

	void SetUp(int _type, float pos_x, float pos_y);
	int GetType() const;

	void SetPositionX(float x);
	float GetPositionX() const;
	void SetPositionY(float y);
	float GetPositionY() const;
	void SetPosition(float x, float y);
	void SetInDangerous(bool _inDangerous);
	bool GetInDangerous() const;
};

#endif