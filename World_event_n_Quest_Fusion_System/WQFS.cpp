#include "WQFS.h"

std::map<std::string, WorldEvent> WQFS::worldEvents;
std::map<std::string, NPC> WQFS::npcs;
std::map<std::string, Item> WQFS::comps;

WorldEvent WQFS::AddEvent(std::string name, int type, float posX, float posY) {
	std::cout << type << " ";
	WorldEvent newEvent;
	newEvent.SetUp(type, posX, posY);
	std:: cout << newEvent.GetType() << std::endl;
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

WorldEvent& WQFS::GetEvent(std::string name) {
	return worldEvents[name];
}

NPC& WQFS::GetNPC(std::string name) {
	return npcs[name];
}

Item& WQFS::GetItem(std::string name) {
	return comps[name];
}

std::map<std::string, WorldEvent>& WQFS::GetAllEvent() {
	return worldEvents;
}

std::map<std::string, NPC>& WQFS::GetAllNPC() {
	return npcs;
}

std::map<std::string, Item>& WQFS::GetAllItem() {
	return comps;
}

void WQFS::MakeQuest(int eventType, int npcType) {
}