#include "Item.h"

Item::Item()
	:type(0), effect(0) { }

void Item::SetUp(int _type, float _effect) {
	type = _type;
	effect = _effect;
}

void Item::DoEffect() {

}

int Item::getType() {
	return type;
}