#include "Item.h"

Item::Item(std::string _name, int _type, int _effect)
	:name(_name), type(_type), effect(_effect) { }

void Item::DoEffect() {

}

std::string Item::getName() {
	return name;
}

int Item::getType() {
	return type;
}