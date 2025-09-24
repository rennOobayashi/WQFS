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

	WQFS() {}
	void SetCompensation(WorldEvent event, NPC npc);
	void CheckConfirmation();
public:
	//bool eventHappen;
	static std::map<std::string, WorldEvent> worldEvents;
	static std::map<std::string, NPC> npcs;
	static std::map<std::string, Item> comps;

	static WorldEvent AddEvent(std::string name, int type, float posX, float posY);
	static NPC AddNPC(std::string name, int type, float posX, float posY);
	static Item AddItem(std::string name, int type, float effect);

	static WorldEvent GetEvent(std::string name);
	static NPC GetNPC(std::string name);
	static Item GetItem(std::string name);

	static std::map<std::string, WorldEvent> GetAllEvent();
	static std::map<std::string, NPC> GetAllNPC();
	static std::map<std::string, Item> GetAllItem();
};

#endif