#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// 1. Heal
// 2. Weapon
// 3. Trade

class Item
{
private:
	std::string name;
	int type;
	int effect;

	void init();
public:
	Item(std::string _name, int _type, int _effect);
	~Item() {}
	void DoEffect();

	std::string getName();
	int getType();
};

#endif