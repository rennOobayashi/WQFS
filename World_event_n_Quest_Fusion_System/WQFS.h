#ifndef WQFS_H
#define WQFS_H

#include "NPC.h"
#include "WorldEvent.h"
#include "Item.h"

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <map>

typedef std::tuple<std::vector<Item>, int, bool> Quest; // compensation list, type, confirmation
typedef std::pair<NPC*, WorldEvent*> QuestTarget; // npc, event

class WQFS
{
private:
	int questNumber;
	int npcNumber, eventNumber, itemNumber;
	bool isPaused;
	clock_t pauseStart;

	WQFS() : questNumber(0),  npcNumber(0), eventNumber(0), itemNumber(0) { }
	// 복사 방지
	WQFS(const WQFS&) = delete;
	WQFS& operator=(const WQFS&) = delete;
	~WQFS() { };

	void SetCompensation(NPC &npc, WorldEvent &event, int questType);
	bool CheckCollision(float object1X, float object1Y, float object1SizeX, float object1SizeY, float object2X, float object2Y, float object2SizeX, float object2SizeY);
public:
	static WQFS& GetInstance() {
		static WQFS instance;
		return instance;
	}

	//bool eventHappen;
	static std::map<std::string, WorldEvent> worldEvents;
	static std::map<std::string, NPC> npcs;
	static std::map<std::string, Item> comps;
	static std::map<int, Quest> questList; //quest number, compensation list
	static std::vector<QuestTarget> QuestTargetObjects; //npc, Event
	static std::map<int, int> questRemaining;

	static void MakeQuest(NPC &npc, WorldEvent &event);
	static  std::vector<Item> CompleteQuest(NPC &npc);

	static WorldEvent AddEvent(std::string name, int type, int hp, float posX, float posY, float sizeX, float sizeY, double maxTime, double duration, double collidDelay);
	static NPC AddNPC(std::string name, int type, float posX, float posY, float sizeX, float sizeY, double maxTime);
	static Item AddItem(std::string name, int type, float effect, int rarity);

	static WorldEvent& GetEvent(std::string name);
	static NPC& GetNPC(std::string name);
	static Item& GetItem(std::string name);

	static void CheckQuest(std::map<Item, int>& inventory, float playerSizeX, float playerSizeY, float playerX, float playerY);
	
	static void CheckEvent();

	static void Pause();
	static void Resume();

	static void DiscountRemainingObstacles(int questNumber);

	static std::vector<std::string> GetQuestListByString(int maxQusetList);

	static void Clear();
};

#endif