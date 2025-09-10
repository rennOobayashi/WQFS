#ifndef WQFS_H
#define WQFS_H

#include <iostream>
#include <vector>

class WQFS
{
private:
	std::vector<std::string> world_events;
	std::vector<std::string> npcs;
	std::vector<std::string> comps;

	void SetCompensation(std::string comp);
	void CheckConfirmation();
public:
	WQFS();
	~WQFS();

	void AddEvent();
	void AddNPC();
	void AddItem();
	void DoEvent();
};

#endif