#include "NPC.h"

NPC::NPC() : inDangerous(false), type(0), positionX(0), positionY(0) { }

void NPC::SetUp(int _type, float pos_x, float pos_y) {
	type = _type;
	positionX = pos_x;
	positionY = pos_y;
}

int NPC::GetType() const {
	return type;
}

void NPC::SetInDangerous(bool _inDangerous) {
	inDangerous = _inDangerous;
}

bool NPC::GetInDangerous() const {
	return inDangerous;
}

void NPC::SetPositionX(float x) {
	positionX = x;
}

float NPC::GetPositionX() const {
	return positionX;
}

void NPC::SetPositionY(float y) {
	positionY = y;
}

float NPC::GetPositionY() const {
	return positionY;
}

void NPC::SetPosition(float x, float y) {
	positionX = x;
	positionY = y;
}