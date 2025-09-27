#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// Example item types:
// 0. HP heal
// 1. MP heal
// 2. Weapon
// 3. Collectible

class Item
{
private:
	std::string name;
	int type;
	float effect;

	void init();
public:
	Item();
	~Item() {}

	void SetUp(int _type, float _effect);
	float GetEffect() const;
	int GetType() const;
};

#endif