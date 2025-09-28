#include "WQFS.h"


bool RandomInRange(int prob) {
	int random = (rand() % 100) + 1;

	//std::cout << random << " " << prob << " " << (random > prob) << std::endl;

	if (random > prob) {
		return false;
	}
	else {
		return true;
	}
}
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

Item WQFS::AddItem(std::string name, int type, float effect, int rarity) {
	Item newItem;
	newItem.SetUp(name, type, effect, rarity);
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

void WQFS::MakeQuest(NPC npc, WorldEvent event) {
	WQFS::GetInstance().SetCompensation(npc);

	std::cout << "보상 ";

	for (int i = 0; i < WQFS::GetInstance().questList[WQFS::GetInstance().questNumber - 1].size(); i++) {
		std::cout << WQFS::GetInstance().questList[WQFS::GetInstance().questNumber - 1][i].GetName() << " ";
	}
	std::cout << std::endl;

	switch (event.GetType()) {
	case 0: WQFS().MonsterEvent(npc.GetType());
		break;
	case 1: WQFS().StaticEvent(npc.GetType());
		break;
	case 2: WQFS().MonsterEvent(npc.GetType());
		break;
	default: std::cout << "Wrong event type!" << std::endl;
		break;
	}
}

void WQFS::SetCompensation(NPC npc) {
	std::vector<Item> compList;
	int allComp = 1;
	bool isHp = false;
	bool isMp = false;
	bool isWeapon = false;
	bool isExchange = false;

	srand((unsigned int)time(NULL));

	for (const auto& comp : comps) {
		if (isHp && isMp && isWeapon && isExchange) {
			break;
		}
		else if (!isHp && comp.second.GetType() == 0) {
			isHp = true;
			continue;
		}
		else if (!isMp && comp.second.GetType() == 1 ) {
			isMp = true;
			continue;
		}
		else if (!isWeapon && comp.second.GetType() == 2) {
			isWeapon = true;
			continue;
		}
		else if (!isExchange && comp.second.GetType() == 3) {
			isExchange = true;
			continue;
		}

	}

	switch (npc.GetType()) {
		case 0:
			if ((isExchange && isHp) && RandomInRange(10)) {
				allComp = 2;

				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0 || comp.second.GetType() == 3) && comp.second.GetRarity() <= 1) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isExchange && RandomInRange(60)) {
				for (const auto& comp : comps) {
					if (comp.second.GetType() == 3 && comp.second.GetRarity() <= 1) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isHp) {
				for (const auto& comp : comps) {
					if (comp.second.GetType() == 0 && comp.second.GetRarity() <= 1) {
						compList.push_back(comp.second);
					}
				}
			}
			break;
		case 1:
			if ((isExchange && isMp && isHp) && RandomInRange(5)) {
				allComp = 3;

				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0 || comp.second.GetType() == 1 || comp.second.GetType() == 3) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (RandomInRange(10)) {
				allComp = 2;

				if ((isExchange && isHp)) {
					for (const auto& comp : comps) {
						if ((comp.second.GetType() == 0 || comp.second.GetType() == 3) && comp.second.GetRarity() <= 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isExchange && isMp)) {
					for (const auto& comp : comps) {
						if ((comp.second.GetType() == 1 || comp.second.GetType() == 3) && comp.second.GetRarity() <= 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else {
					for (const auto& comp : comps) {
						if ((comp.second.GetType() == 0 || comp.second.GetType() == 1) && comp.second.GetRarity() <= 3) {
							compList.push_back(comp.second);
						}
					}
				}
			}
			else if (isHp && RandomInRange(40)) {
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isMp && RandomInRange(30)) {
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 1) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else  {
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 3) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			break;
		case 2:
			if ((isWeapon && isHp) && RandomInRange(10)) {
				allComp = 2;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0 || comp.second.GetType() == 2) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isWeapon && RandomInRange(60)) {
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 2) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isHp) {
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			break;
		case 3:
			if ((isExchange && isMp && isHp && isWeapon) && RandomInRange(5)) {
				allComp = 4;

				for (const auto& comp : comps) {
					compList.push_back(comp.second);
				}
			}
			else if (RandomInRange(15)) {
				allComp = 3;

				if ((isExchange && isMp && isWeapon)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 1 || comp.second.GetType() == 2 || comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isExchange && isHp && isWeapon)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0 || comp.second.GetType() == 2 || comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isExchange && isHp && isMp)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0 || comp.second.GetType() == 1 || comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isMp && isHp && isWeapon)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0 || comp.second.GetType() == 1 || comp.second.GetType() == 2) {
							compList.push_back(comp.second);
						}
					}
				}
			}
			else if (RandomInRange(30)) {
				allComp = 2;

				if ((isExchange && isHp)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0 || comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isExchange && isMp)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 1 || comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isExchange && isWeapon)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 2 || comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isHp && isWeapon)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0 || comp.second.GetType() == 2) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isMp && isWeapon)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 1 || comp.second.GetType() == 2) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isHp && isMp)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0 || comp.second.GetType() == 1) {
							compList.push_back(comp.second);
						}
					}
				}
			}
			else {
				if ((isExchange) && RandomInRange(25)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 3) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isWeapon) && RandomInRange(25)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 2) {
							compList.push_back(comp.second);
						}
					}
				}
				else if ((isMp) && RandomInRange(25)) {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 1) {
							compList.push_back(comp.second);
						}
					}
				}
				else {
					for (const auto& comp : comps) {
						if (comp.second.GetType() == 0) {
							compList.push_back(comp.second);
						}
					}
				}
			}
			break;
		default: std::cout << "Wrong NPC type!" << std::endl;
			break;
	}

	for (int i = 0 ; i < allComp; i++) {
		int randomIndex = rand() % compList.size();

		questList[WQFS::GetInstance().questNumber].push_back(compList[randomIndex]);
	}

	WQFS::GetInstance().questNumber++;
}
std::vector<Item> WQFS::GetCompensation(NPC npc)  {
	return questList[WQFS::GetInstance().questNumber];
}

void WQFS::MonsterEvent(int npcType)  {

}

void WQFS::DynamicEvent(int npcType)  {

}

void WQFS::StaticEvent(int npcType)  {

}