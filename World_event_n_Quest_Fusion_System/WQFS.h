#ifndef WQFS_H
#define WQFS_H

#include "NPC.h"
#include "WorldEvent.h"
#include "Item.h"

#include <iostream>
#include <vector>
#include <Windows.h>
#include <time.h>

class WQFS
{
private:
	std::vector<WorldEvent> world_events;
	std::vector<NPC> npcs;
	std::vector<Item> comps;
	
	clock_t start_time;
	double time_limit;
	int fame;

	void init();
	void SetCompensation(WorldEvent event, NPC npc);
	void CheckConfirmation();
public:
	WQFS(int _fame);
	~WQFS();

	void AddEvent();
	void AddNPC();
	void AddItem();
	void Test();
};

#endif