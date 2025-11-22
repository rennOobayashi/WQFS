#include "NPC.h"

NPC::NPC() : number(0), inDangerous(false), canDangerous(false), type(0), subType(-1), positionX(0.0f), positionY(0.0f), positionZ(0.0f), sizeX(00.0f), sizeY(0.0f), sizeZ(0.0f), questNumber(-1), start(clock()), timer(0.0f), maxTime(5.0f) {}

void NPC::SetUp(int _number, int _type, float posX, float posY, float _sizeX, float _sizeY, double _maxTime) {
	number = _number;
	type = _type;
	positionX = posX;
	positionY = posY;
	sizeX = _sizeX;
	sizeY = _sizeY;
	maxTime = _maxTime;
	canDangerous = true;
}

void NPC::SetUp(int _number, int _type, int _subType, float posX, float posY, float _sizeX, float _sizeY, double _maxTime) {
	number = _number;
	type = _type;
	subType = _subType;
	positionX = posX;
	positionY = posY;
	sizeX = _sizeX;
	sizeY = _sizeY;
	maxTime = _maxTime;
	canDangerous = true;
}

void NPC::Timer() {
	if (!canDangerous && timer <= maxTime + pauseDuration) {
		timer = (float)(clock() - start) / CLOCKS_PER_SEC;
	}
	else {
		canDangerous = true;
	}
}

void NPC::ResetTimer() {
	start = clock();
	timer = 0.0f;
	pauseDuration = 0.0f;
	canDangerous = false;
}

int NPC::GetType() const {
	return type;
}

int NPC::GetSubType() const {
	return subType;
}

void NPC::SetInDangerous(bool _inDangerous) {
	inDangerous = _inDangerous;
}

bool NPC::GetInDangerous() const {
	return inDangerous;
}

void NPC::SetCanDangerous(bool _canDangerous) {
	canDangerous = _canDangerous;
}

bool NPC::GetCanDangerous() const {
	return canDangerous;
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

void NPC::SetPositionZ(float z) {
	positionZ = z;
}

float NPC::GetPositionZ() const {
	return positionZ;
}

void NPC::SetPosition(float x, float y, float z) {
	positionX = x;
	positionY = y;
	positionZ = z;
}


void NPC::SetPosition(float x, float y) {
	positionX = x;
	positionY = y;
}

void NPC::SetSizeX(float x) {
	sizeX = x;
}

float NPC::GetSizeX() const {
	return sizeX;
}

void NPC::SetSizeY(float y) {
	sizeY = y;
}
float NPC::GetSizeY() const {
	return sizeY;
}

void NPC::SetSizeZ(float z) {
	sizeY = z;
}
float NPC::GetSizeZ() const {
	return sizeZ;
}

void NPC::SetSize(float x, float y) {
	sizeX = x;
	sizeY = y;
}

void NPC::SetSize(float x, float y, float z) {
	sizeX = x;
	sizeY = y;
	sizeZ = z;
}

void NPC::setQuestNumber(int n) {
	questNumber = n;
}

int NPC::getQuestNumber() const {
	return questNumber;
}

void NPC::SetPauseDuration(float duration) {
	pauseDuration = duration;
}
float NPC::GetPauseDuration() const {
	return pauseDuration;
}