#include "WorldEvent.h"

WorldEvent::WorldEvent() 
	: number(-1), type(-1), subType(-1), hp(0), positionX(0.0f), positionY(0.0f), positionZ(0.0f), sizeX(0.0f), sizeY(0.0f), sizeZ(0.0f), questNumber(-1), isVisible(true), doEvent(false), isCanCollid(false), start(clock()), eventStart(0), eventTimer(0.0f), maxTime(0.0f), duration(0.0f), durationTimer(0.0f), collideDelay(0.0f), pauseDuration(0.0f), isMove(false), errorValue(0) { }

void WorldEvent::SetUp(int _number, int _type, int _hp, float posX, float posY, float _sizeX, float _sizeY, float _maxTime, float _duration, float _collideDelay, int _errorValue) {
	number = _number;
	type = _type;
	if (type == 0) {
		hp = _hp;
	}
	else {
		hp = -1;
	}

	positionX = posX;
	positionY = posY;
	sizeX = _sizeX;
	sizeY = _sizeY;

	if (type != 0) {
		maxTime = _maxTime;
		duration = _duration;
		collideDelay = _collideDelay;
		errorValue = _errorValue;

		errorTime = ((rand() % int(maxTime)) + 1) + errorValue;
		if (errorTime < errorValue) {
			errorTime = errorValue;
		}
	}
	else {
		maxTime = -1.0f;
		_duration = -1.0f;
		collideDelay = 0.0f;
		errorValue = _errorValue;
	}
	
}

void WorldEvent::SetUp(int _number, int _type, int _subType, int _hp, float posX, float posY, float _sizeX, float _sizeY, float _maxTime, float _duration, float _collideDelay, int _errorValue) {
	number = _number;
	type = _type;
	subType = _subType;
	if (type == 0) {
		hp = _hp;
	}
	else {
		hp = -1;
	}

	positionX = posX;
	positionY = posY;
	sizeX = _sizeX;
	sizeY = _sizeY;

	if (type != 0) {
		maxTime = _maxTime;
		duration = _duration;
		collideDelay = _collideDelay;
		errorValue = _errorValue;

		errorTime = ((rand() % int(maxTime)) + 1) + errorValue;
		if (errorTime < errorValue) {
			errorTime = errorValue;
		}
	}
	else {
		maxTime = -1.0f;
		_duration = -1.0f;
		collideDelay = 0.0f;
		errorValue = _errorValue;
	}

}

void WorldEvent::Timer() {
	if (maxTime <= 0) {
		return;
	}

	if (!doEvent && eventTimer > errorTime + pauseDuration) {
		//std::cout << "이벤트 시작" << std::endl;
		eventStart = clock();
		doEvent = true;
	}

	if (!isCanCollid && eventTimer > errorTime + collideDelay + pauseDuration) {
		//std::cout << "충돌 시작" << collideDelay << std::endl;
		isCanCollid = true;
	}
	else if (!isCanCollid && eventTimer <= errorTime + collideDelay + pauseDuration) {
		eventTimer = (float)(clock() - start) / CLOCKS_PER_SEC;
	}
}

void WorldEvent::ResetTimer() {
	if (duration <= 0) {
		return;
	}

	if (durationTimer <= duration + pauseDuration) {
		durationTimer = (float)(clock() - eventStart) / CLOCKS_PER_SEC;
	}
	else {
		//std::cout << "이벤트 끝" << std::endl;
		start = clock();
		eventTimer = 0.0f;
		durationTimer = 0.0f;
		pauseDuration = 0.0f;
		doEvent = false;
		isCanCollid = false;

		errorTime = ((rand() % int(maxTime)) + 1) + errorValue;

		if (errorTime < errorValue) {
			errorTime = errorValue;
		}
	}
}


int WorldEvent::GetType() const {
	return type;
}

int WorldEvent::GetSubType() const {
	return subType;
}

void WorldEvent::SetPositionX(float x) {
	positionX = x;
}

float WorldEvent::GetPositionX() const {
	return positionX;
}
void WorldEvent::SetPositionY(float y) {
	positionY = y;
}

float WorldEvent::GetPositionY() const {
	return positionY;
}

void WorldEvent::SetPositionZ(float z) {
	positionZ = z;
}

float WorldEvent::GetPositionZ() const {
	return positionZ;
}

void WorldEvent::SetPosition(float x, float y) {
	positionX = x;
	positionY = y;
}

void WorldEvent::SetPosition(float x, float y, float z) {
	positionX = x;
	positionY = y;
	positionZ = z;
}


void WorldEvent::SetSizeX(float x) {
	sizeX = x;
}

float WorldEvent::GetSizeX() const {
	return sizeX;
}

void WorldEvent::SetSizeY(float y) {
	sizeY = y;
}
float WorldEvent::GetSizeY() const {
	return sizeY;
}

void WorldEvent::SetSizeZ(float z) {
	sizeZ = z;
}
float WorldEvent::GetSizeZ() const {
	return sizeZ;
}

void WorldEvent::SetSize(float x, float y) {
	sizeX = x;
	sizeY = y;
}

void WorldEvent::SetSize(float x, float y, float z) {
	sizeX = x;
	sizeY = y;
	sizeZ = z;
}

void WorldEvent::setQuestNumber(int n) {
	questNumber = n;
}

int WorldEvent::getQuestNumber() const {
	return questNumber;
}

void WorldEvent::setHp(int _hp) {
	if (hp == -1) {
		return;
	}
	
	if (_hp < 0) {
		hp = 0;
	}
	else {
		hp = _hp;
	}
}

int WorldEvent::getHp() const {
	return hp;
}

int WorldEvent::takeDamage(int damage) {
	if (type == 0) {
		hp -= damage;
		if (hp < 0) {
			hp = 0;
		}
	}

	std::cout << hp << std::endl;
	return hp;
}

void WorldEvent::setVisible(bool b) {
	isVisible = b;
}

bool WorldEvent::getVisible() const {
	return isVisible;
}

void WorldEvent::setDoEvent(bool b) {
	doEvent = b;
}

bool WorldEvent::getDoEvent() const {
	return doEvent;
}

void WorldEvent::SetIsCanCollid(bool b) {
	isCanCollid = b;
}

bool WorldEvent::GetIsCanCollid() const {
	return isCanCollid;
}

void WorldEvent::SetPauseDuration(float duration) {
	pauseDuration = duration;
}
float WorldEvent::GetPauseDuration() const {
	return pauseDuration;
}

void WorldEvent::SetIsMove(bool b) {
	isMove = b;
}
bool WorldEvent::GetIsMove() const {
	return isMove;
}