#ifndef NPC_H
#define NPC_H

#include <iostream>

// 1. normal
// 2. Item dealer
// 3. weapon dealer
// 4. peddler

class NPC
{
private:
	std::string name;
	int type;
	float position_x, position_y;

	void init();
public:

	NPC(std::string _name, int _type, float pos_x, float pos_y);
	~NPC() { }

	void move();
	std::string getName();
	int getType();
};

#endif