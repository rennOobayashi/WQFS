#include "Item.h"

Item::Item()
	:type(0), effect(0) { }

void Item::SetUp(int _type, float _effect) {
	type = _type;
	effect = _effect;
}

float Item::GetEffect() {
	return effect;
}

int Item::GetType() {
	return type;
}