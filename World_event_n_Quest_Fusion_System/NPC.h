#ifndef NPC_H
#define NPC_H

#include <iostream>

// Example NPC types:
// 1. normal
// 2. Item dealer
// 3. weapon dealer
// 4. peddler

class NPC
{
private:
	std::string name;
	int type;
	float positionX, positionY;
public:
	bool inDangerous;
	NPC();
	~NPC() { }

	void SetUp(int _type, float pos_x, float pos_y);
	int getType();
};

#endif