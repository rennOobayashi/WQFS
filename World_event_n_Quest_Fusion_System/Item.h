#ifndef ITEM_H
#define ITEM_H

#include <iostream>

// 기본 아이템 타입:
// 0. HP 회복
// 1. MP 회복
// 2. 무기
// 3. 환전

class Item
{
private:
	std::string name;
	int type;
	int rarity; // 0~4
	float effect;

	void init();
public:
	Item();
	~Item() {}

	void SetUp(std::string _name, int _type, float _effect, int rarity);
	std::string GetName() const;
	float GetEffect() const;
	int GetType() const;
	int GetRarity() const;
};

#endif