#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// default Item type:
// 0. HP heal
// 1. MP heal
// 2. Weapon
// 3. Exchange

class Item
{
private:
	int number;
	std::string name;
	int type;
	int rarity; // 0~4
	float effect;
public:
	Item();
	~Item() {}

	void SetUp(int _number, std::string _name, int _type, float _effect, int rarity);
	std::string GetName() const;
	float GetEffect() const;
	int GetType() const;
	int GetRarity() const;


	bool operator<(const Item& other) const {
		return this->number < other.number;
	}

	bool operator=(const Item& other) const {
		return this->number == other.number;
	}
};

#endif