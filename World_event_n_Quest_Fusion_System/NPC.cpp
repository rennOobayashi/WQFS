#include "NPC.h"

NPC::NPC() : inDangerous(false) { }

void NPC::SetUp(int _type, float pos_x, float pos_y) {
	type = _type;
	positionX = pos_x;
	positionY = pos_y;
}

int NPC::getType() {
	return type;
}