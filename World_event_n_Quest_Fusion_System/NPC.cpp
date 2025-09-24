#include "NPC.h"

NPC::NPC() : inDangerous(false), type(0), positionX(0), positionY(0) { }

void NPC::SetUp(int _type, float pos_x, float pos_y) {
	type = _type;
	positionX = pos_x;
	positionY = pos_y;
}

int NPC::getType() const {
	return type;
}