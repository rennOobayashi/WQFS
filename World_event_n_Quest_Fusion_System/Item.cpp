#include "Item.h"

Item::Item()
	: number(0), type(0), effect(0), rarity(0) { }

void Item::SetUp(int _number, std::string _name, int _type, float _effect, int rarity) {
	number = _number;
	name = _name;
	type = _type;
	effect = _effect;
}

std::string Item::GetName() const{
	return name;
}

float Item::GetEffect() const{
	return effect;
}

int Item::GetType() const{
	return type;
}

int Item::GetRarity() const {
	return rarity;
}