#ifndef WQFS_H
#define WQFS_H

#include "NPC.h"
#include "WorldEvent.h"
#include "Item.h"

#include <iostream>
#include <vector>
#include <Windows.h>
#include <time.h>
#include <map>

typedef std::tuple<std::vector<Item>, bool> Quest; // compensation list, confirmation
//추후 Item Type으로도 가능하게 변경
typedef std::tuple<std::vector<int>, bool> QuestByType; // compensation list, confirmation
typedef std::pair<NPC*, WorldEvent*> QuestTarget; // npc, event

class WQFS
{
private:
	int questNumber;
	int npcNumber, eventNumber, itemNumber;
	float dangerousDelay, dangerousDelayTime;

	WQFS() : questNumber(0),  npcNumber(0), eventNumber(0), itemNumber(0), dangerousDelay(10), dangerousDelayTime(5) {}
	// 복사 방지
	WQFS(const WQFS&) = delete;
	WQFS& operator=(const WQFS&) = delete;
	~WQFS() { };

	void SetCompensation(NPC &npc, WorldEvent &event);
	void MonsterEvent(int npcType) ;
	void DynamicEvent(int npcType) ;
	void StaticEvent(int npcType) ;
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
	static std::map<int, QuestByType> questListByType; //quest number, compensation list
	static std::vector<QuestTarget> QuestTargetObjects; //npc, Event

	static void MakeQuest(NPC &npc, WorldEvent &event);
	static  std::vector<Item> CompleteQuest(NPC &npc);
	static  std::vector<int> CompleteQuestByType(NPC& npc);

	static WorldEvent AddEvent(std::string name, int type, int hp, float posX, float posY, float sizeX, float sizeY);
	static NPC AddNPC(std::string name, int type, float posX, float posY, float sizeX, float sizeY);
	static Item AddItem(std::string name, int type, float effect, int rarity);

	static WorldEvent& GetEvent(std::string name);
	static NPC& GetNPC(std::string name);
	static Item& GetItem(std::string name);

	static void CheckEvent(std::map<Item, int>& inventory, float playerSizeX, float playerSizeY, float playerX, float playerY);
	static void CheckEvent(std::map<int, int>& inventory, float playerSizeX, float playerSizeY, float playerX, float playerY);

	static void SetDangerousDelay(float delay);
	static float GetDangerousDelay();

	static void Clear();
};

#endif