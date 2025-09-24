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
	int type;
public:
	float positionX, positionY;
	bool inDangerous;
	NPC();
	~NPC() { }

	void SetUp(int _type, float pos_x, float pos_y);
	int getType() const;
};

#endif