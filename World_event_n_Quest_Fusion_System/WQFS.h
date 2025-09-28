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

class WQFS
{
private:
	int questNumber;

	WQFS() : questNumber(0) {}
	// 복사 방지
	WQFS(const WQFS&) = delete;
	WQFS& operator=(const WQFS&) = delete;
	~WQFS() {};

	void SetCompensation(NPC npc);
	std::vector<Item> GetCompensation(NPC npc) ;
	void CheckConfirmation();
	void MonsterEvent(int npcType) ;
	void DynamicEvent(int npcType) ;
	void StaticEvent(int npcType) ;
	std::map<int, std::vector<Item>> questList; //quest number, compensation list
public:
	static WQFS& GetInstance() {
		static WQFS instance;
		return instance;
	}

	//bool eventHappen;
	static std::map<std::string, WorldEvent> worldEvents;
	static std::map<std::string, NPC> npcs;
	static std::map<std::string, Item> comps;

	static void MakeQuest(NPC npc, WorldEvent event);
	static void CompleteQuest();

	static WorldEvent AddEvent(std::string name, int type, float posX, float posY);
	static NPC AddNPC(std::string name, int type, float posX, float posY);
	static Item AddItem(std::string name, int type, float effect, int rarity);

	static WorldEvent& GetEvent(std::string name);
	static NPC& GetNPC(std::string name);
	static Item& GetItem(std::string name);

	static std::map<std::string, WorldEvent>& GetAllEvent();
	static std::map<std::string, NPC>& GetAllNPC();
	static std::map<std::string, Item>& GetAllItem();
};

#endif