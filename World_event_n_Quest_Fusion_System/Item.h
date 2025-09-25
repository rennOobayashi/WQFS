#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// Example item types:
// 0. Heal
// 1. Weapon
// 2. Collectible

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
	float GetEffect();
	int GetType();
};

#endif