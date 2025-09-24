#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// Example item types:
// 1. Heal
// 2. Weapon
// 3. Trade

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
	int getType();

	bool operator<(const Item& other) const {
		return type < other.type;
	};
};

#endif