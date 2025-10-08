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
std::map<int, Quest> WQFS::questList;
std::map<NPC, WorldEvent> WQFS::QuestTargetObjects;

WorldEvent WQFS::AddEvent(std::string name, int type, float posX, float posY) {
	//std::cout << type << " ";
	WorldEvent newEvent;
	newEvent.SetUp(WQFS::GetInstance().eventNumber++, type, posX, posY);
	//std:: cout << newEvent.GetType() << std::endl;
	worldEvents[name] = newEvent;
	return newEvent;
}

NPC WQFS::AddNPC(std::string name, int type, float posX, float posY) {
	NPC newNPC;
	newNPC.SetUp(WQFS::GetInstance().npcNumber++, type, posX, posY);
	npcs[name] = newNPC;
	return newNPC;
}

Item WQFS::AddItem(std::string name, int type, float effect, int rarity) {
	Item newItem;
	newItem.SetUp(WQFS::GetInstance().itemNumber++, name, type, effect, rarity);
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

void WQFS::Clear() {
	worldEvents.clear();
	npcs.clear();
	comps.clear();
}

void WQFS::MakeQuest(NPC &npc, WorldEvent &event) {
	WQFS::GetInstance().SetCompensation(npc, event);

	std::cout << "보상 ";

	for (int i = 0; i < std::get<0>(WQFS::GetInstance().questList[WQFS::GetInstance().questNumber - 1]).size(); i++) {
		std::cout << std::get<0>(WQFS::GetInstance().questList[WQFS::GetInstance().questNumber - 1])[i].GetName() << " ";
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

void WQFS::SetCompensation(NPC &npc, WorldEvent& event) {
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

	std::get<0>(questList[WQFS::GetInstance().questNumber]) = compList;

	std::get<1>(questList[WQFS::GetInstance().questNumber]) = false;

	npc.setQuestNumber(WQFS::GetInstance().questNumber);
	event.setQuestNumber(WQFS::GetInstance().questNumber);

	WQFS::GetInstance().questNumber++;

	QuestTargetObjects[npc] = event;
}


std::vector<Item> WQFS::CompleteQuest(NPC &npc)  {
	if (!std::get<1>(questList[npc.getQuestNumber()])) {
		std::get<1>(questList[npc.getQuestNumber()]) = true;
		npc.SetInDangerous(false);

		std::cout << "퀘스트 완료!" << std::endl;

		return std::get<0>(questList[npc.getQuestNumber()]);
	}
	else {
		std::cout << "이미 완료한 퀘스트입니다!" << std::endl;
		return std::vector<Item>();
	}
}

void WQFS::MonsterEvent(int npcType)  {

}

void WQFS::DynamicEvent(int npcType)  {

}

void WQFS::StaticEvent(int npcType)  {

}