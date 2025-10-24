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
typedef std::pair<NPC*, WorldEvent*> QuestTarget; // npc, event

class WQFS
{
private:
	int questNumber;
	int npcNumber, eventNumber, itemNumber;

	WQFS() : questNumber(0),  npcNumber(0), eventNumber(0), itemNumber(0) {}
	// 복사 방지
	WQFS(const WQFS&) = delete;
	WQFS& operator=(const WQFS&) = delete;
	~WQFS() { };

	void SetCompensation(NPC &npc, WorldEvent &event);
	void MonsterEvent(int npcType) ;
	void DynamicEvent(int npcType) ;
	void StaticEvent(int npcType) ;
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

	static void MakeQuest(NPC &npc, WorldEvent &event);
	static  std::vector<Item> CompleteQuest(NPC &npc);

	static WorldEvent AddEvent(std::string name, int type, int hp, float posX, float posY);
	static NPC AddNPC(std::string name, int type, float posX, float posY);
	static Item AddItem(std::string name, int type, float effect, int rarity);

	static WorldEvent& GetEvent(std::string name);
	static NPC& GetNPC(std::string name);
	static Item& GetItem(std::string name);

	static void CheckEvent(std::map<Item, int>& inventory);

	static void Clear();
};

#endif