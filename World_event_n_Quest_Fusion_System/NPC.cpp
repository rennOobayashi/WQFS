#include "NPC.h"

NPC::NPC(std::string _name, int _type, float pos_x, float pos_y) 
	:name(_name), type(_type), position_x(pos_x), position_y(pos_y) { }

void NPC::move() {
	std::cout << "NPC " << name << "moving" << std::endl;
}

std::string NPC::getName() {
	return name;
}

int NPC::getType() {
	return type;
}