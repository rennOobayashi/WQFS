#include "Item.h"

Item::Item()
	:type(0), effect(0), rarity(0) { }

void Item::SetUp(std::string _name, int _type, float _effect, int rarity) {
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