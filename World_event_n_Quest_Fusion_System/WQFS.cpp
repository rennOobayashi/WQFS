#include "WQFS.h"

std::map<std::string, WorldEvent> WQFS::worldEvents;
std::map<std::string, NPC> WQFS::npcs;
std::map<std::string, Item> WQFS::comps;

WorldEvent WQFS::AddEvent(std::string name, float posX, float posY) {
	WorldEvent newEvent;
	newEvent.SetUp(posX, posY);
	worldEvents[name] = newEvent;
	return newEvent;
}

NPC WQFS::AddNPC(std::string name, int type, float posX, float posY) {
	NPC newNPC;
	newNPC.SetUp(type, posX, posY);
	npcs[name] = newNPC;
	return newNPC;
}

Item WQFS::AddItem(std::string name, int type, float effect) {
	Item newItem;
	newItem.SetUp(type, effect);
	comps[name] = newItem;
	return newItem;
}