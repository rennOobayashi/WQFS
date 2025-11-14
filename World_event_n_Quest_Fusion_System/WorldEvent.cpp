#include "WorldEvent.h"

WorldEvent::WorldEvent() 
	: number(-1), type(-1), hp(0), positionX(0), positionY(0), sizeX(0), sizeY(0), questNumber(-1), isVisible(true), doEvent(false), isCanCollid(false), start(clock()), eventStart(0), eventTimer(0.0f), maxTime(0.0f), duration(0.0f), durationTimer(0.0f), collideDelay(0.0f), isMove(false) { }

void WorldEvent::SetUp(int _number, int _type, int _hp, float posX, float posY, float _sizeX, float _sizeY, double _maxTime, double _duration, double _collideDelay) {
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
	}
	else {
		maxTime = -1.0f;
		_duration = -1.0f;
		collideDelay = 0.0f;
	}
}

void WorldEvent::Timer() {
	if (maxTime == -1) {
		return;
	}

	if (!doEvent && eventTimer > maxTime + pauseDuration) {
		//std::cout << "이벤트 시작" << std::endl;
		eventStart = clock();
		doEvent = true;
	}

	if (!isCanCollid && eventTimer > maxTime + collideDelay + pauseDuration) {
		//std::cout << "충돌 시작" << collideDelay << std::endl;
		isCanCollid = true;
	}
	else if (!isCanCollid && eventTimer <= maxTime + collideDelay + pauseDuration) {
		eventTimer = (double)(clock() - start) / CLOCKS_PER_SEC;
	}
}

void WorldEvent::ResetTimer() {
	if (duration == -1) {
		return;
	}

	if (durationTimer <= duration + pauseDuration) {
		durationTimer = (double)(clock() - eventStart) / CLOCKS_PER_SEC;
	}
	else {
		//std::cout << "이벤트 끝" << std::endl;
		start = clock();
		eventTimer = 0.0f;
		durationTimer = 0.0f;
		pauseDuration = 0.0f;
		doEvent = false;
		isCanCollid = false;
	}
}


int WorldEvent::GetType() const {
	return type;
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

void WorldEvent::SetPosition(float x, float y) {
	positionX = x;
	positionY = y;
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

void WorldEvent::SetSize(float x, float y) {
	sizeX = x;
	sizeY = y;
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

void WorldEvent::takeDamage(int damage) {
	if (type == 0) {
		hp -= damage;
		if (hp < 0) {
			hp = 0;
		}
	}

	std::cout << hp << std::endl;
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

void WorldEvent::SetPauseDuration(double duration) {
	pauseDuration = duration;
}
double WorldEvent::GetPauseDuration() const {
	return pauseDuration;
}

void WorldEvent::SetIsMove(bool b) {
	isMove = b;
}
bool WorldEvent::GetIsMove() const {
	return isMove;
}