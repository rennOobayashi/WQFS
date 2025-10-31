#include "NPC.h"

NPC::NPC() : number(0), inDangerous(false), canDangerous(true), type(0), positionX(0), positionY(0), sizeX(0), sizeY(0), questNumber(-1), start(clock()), timer(10.0f), maxTime(5.0f) {}

void NPC::SetUp(int _number, int _type, float posX, float posY, float _sizeX, float _sizeY, double _maxTime) {
	number = _number;
	type = _type;
	positionX = posX;
	positionY = posY;
	sizeX = _sizeX;
	sizeY = _sizeY;
	maxTime = _maxTime;
}

void NPC::Timer() {
	if (!canDangerous && timer <= maxTime) {
		timer = (double)(clock() - start) / CLOCKS_PER_SEC;
	}
	else {
		canDangerous = true;
	}
}

void NPC::ResetTimer() {
	std::cout << "딜레이 시작" << std::endl;
	start = clock();
	timer = 0.0f;
	canDangerous = false;
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

void NPC::SetCanDangerous(bool _canDangerous) {
	canDangerous = _canDangerous;
}

bool NPC::GetCanDangerous() const {
	return positionX;
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

void NPC::SetSize(float x, float y) {
	sizeX = x;
	sizeY = y;
}


void NPC::setQuestNumber(int n) {
	questNumber = n;
}

int NPC::getQuestNumber() const {
	return questNumber;
}