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
std::vector<QuestTarget> WQFS::QuestTargetObjects;
std::map<int, int> WQFS::questRemaining;

WorldEvent WQFS::AddEvent(std::string name, int type, int hp, float posX, float posY, float sizeX, float sizeY, float maxTime, float duration, float collidDelay, float errorValue) {
	//std::cout << type << " ";
	WorldEvent newEvent;
	newEvent.SetUp(WQFS::GetInstance().eventNumber++, type, hp, posX, posY, sizeX, sizeY, maxTime, duration, collidDelay, errorValue);
	std:: cout << newEvent.getHp() << std::endl;
	WQFS::GetInstance().worldEvents[name] = newEvent;

	std::cout << collidDelay << "s" << std::endl;

	return newEvent;
}

NPC WQFS::AddNPC(std::string name, int type, float posX, float posY, float sizeX, float sizeY, double maxTime) {
	NPC newNPC;
	newNPC.SetUp(WQFS::GetInstance().npcNumber++, type, posX, posY, sizeX, sizeY, maxTime);
	WQFS::GetInstance().npcs[name] = newNPC;

	std::cout << newNPC.GetPositionX() << " " << newNPC.GetPositionY() << " " << newNPC.GetSizeX() << " " << newNPC.GetSizeY() << std::endl;
	std::cout << npcs[name].GetPositionX() << " " << npcs[name].GetPositionY() << " " << npcs[name].GetSizeX() << " " << npcs[name].GetSizeY() << std::endl;

	return newNPC;
}

WorldEvent WQFS::AddEvent(std::string name, int type, int subType, int hp, float posX, float posY, float sizeX, float sizeY, float maxTime, float duration, float collidDelay, float errorValue) {
	//std::cout << type << " ";
	WorldEvent newEvent;
	newEvent.SetUp(WQFS::GetInstance().eventNumber++, type, subType, hp, posX, posY, sizeX, sizeY, maxTime, duration, collidDelay, errorValue);
	WQFS::GetInstance().worldEvents[name] = newEvent;

	std::cout << collidDelay << "s" << std::endl;

	return newEvent;
}

NPC WQFS::AddNPC(std::string name, int type, int subType, float posX, float posY, float sizeX, float sizeY, double maxTime) {
	NPC newNPC;
	newNPC.SetUp(WQFS::GetInstance().npcNumber++, type, subType, posX, posY, sizeX, sizeY, maxTime);
	WQFS::GetInstance().npcs[name] = newNPC;

	std::cout << newNPC.GetPositionX() << " " << newNPC.GetPositionY() << " " << newNPC.GetSizeX() << " " << newNPC.GetSizeY() << std::endl;
	std::cout << npcs[name].GetPositionX() << " " << npcs[name].GetPositionY() << " " << npcs[name].GetSizeX() << " " << npcs[name].GetSizeY() << std::endl;

	return newNPC;
}

Item WQFS::AddItem(std::string name, int type, float effect, int rarity) {
	Item newItem;
	newItem.SetUp(WQFS::GetInstance().itemNumber++, name, type, effect, rarity);
	WQFS::GetInstance().comps[name] = newItem;
	return newItem;
}

WorldEvent& WQFS::GetEvent(std::string name) {
	return WQFS::GetInstance().worldEvents[name];
}

NPC& WQFS::GetNPC(std::string name) {
	return WQFS::GetInstance().npcs[name];
}

Item& WQFS::GetItem(std::string name) {
	return WQFS::GetInstance().comps[name];
}


void WQFS::Clear() {
	worldEvents.clear();
	npcs.clear();
	comps.clear();
}

void WQFS::MakeQuest(NPC &npc, WorldEvent &event) {
	if (npc.getQuestNumber() != -1) {
		return;
	}

	int questType = 0;

	int random = rand() % 2;

	if (event.GetType() == 0) {
		if (random == 0) questType = 0;
		else questType = 1;
	}
	else {
		if (random == 0) questType = 2;
		else questType = 3;
	}

	WQFS::GetInstance().SetCompensation(npc, event, questType);

	if (questType == 2) {
		questRemaining[npc.getQuestNumber()] = (rand() % 3) + 3;
	}
	if (questType == 3) {
		questRemaining[npc.getQuestNumber()] = (rand() % 3) + 1;
	}

	std::cout << "보상 ";

	for (int i = 0; i < std::get<0>(WQFS::GetInstance().questList[WQFS::GetInstance().questNumber - 1]).size(); i++) {
		std::cout << std::get<0>(WQFS::GetInstance().questList[WQFS::GetInstance().questNumber - 1])[i].GetName() << " ";
	}
	std::cout << std::endl;
	//std::cout << npc.GetType()  << " " << event.GetType() << std::endl;
}

bool WQFS::CheckCollision(float object1X, float object1Y, float object1SizeX, float object1SizeY, float object2X, float object2Y, float object2SizeX, float object2SizeY) {
	bool collisionX = object1X + object1SizeX >= object2X &&
		object2X + object2SizeX >= object1X;
	bool collisionY = object1Y + object1SizeY >= object2Y &&
		object2Y + object2SizeY >= object1Y;

	return collisionX && collisionY;
}

bool WQFS::CheckCollision3D(float object1X, float object1Y, float object1Z, float object1SizeX, float object1SizeY, float object1SizeZ, float object2X, float object2Y, float object2Z, float object2SizeX, float object2SizeY, float object2SizeZ) {
	bool collisionX = object1X + object1SizeX >= object2X &&
		object2X + object2SizeX >= object1X;
	bool collisionY = object1Y + object1SizeY >= object2Y &&
		object2Y + object2SizeY >= object1Y;
	bool collisionZ = object1Z + object1SizeZ >= object2Z &&
		object2Z + object2SizeZ >= object1Z;

	return collisionX && collisionY && collisionZ;
}

void WQFS::CheckQuest(std::map<Item, int>& inventory, int& questCnt, float playerSizeX, float playerSizeY, float playerX, float playerY) {
	for (auto& npc : WQFS::GetInstance().npcs) {
		if (!npc.second.GetInDangerous() && npc.second.GetCanDangerous()) {
			for (auto& monster : WQFS::GetInstance().worldEvents) {
				if (monster.second.GetType() == 0) {
					if (WQFS::GetInstance().GetEvent(monster.first).getVisible() && WQFS::GetInstance().CheckCollision(npc.second.GetPositionX(), npc.second.GetPositionY(), npc.second.GetSizeX(), npc.second.GetSizeY(), monster.second.GetPositionX(), monster.second.GetPositionY(), monster.second.GetSizeX(), monster.second.GetSizeY())) {
						npc.second.SetInDangerous(true);
						WQFS::GetInstance().MakeQuest(npc.second, WQFS::GetInstance().GetEvent(monster.first));
						std::cout << npc.second.getQuestNumber() << "monster" << std::endl;
					}
				}
			}
			
			for (auto& wEvent : WQFS::GetInstance().worldEvents) {
				if (wEvent.second.GetType() != 0 && wEvent.second.GetIsCanCollid() && WQFS::GetInstance().CheckCollision(npc.second.GetPositionX(), npc.second.GetPositionY(), npc.second.GetSizeX(), npc.second.GetSizeY(), wEvent.second.GetPositionX(), wEvent.second.GetPositionY(), wEvent.second.GetSizeX(), wEvent.second.GetSizeY())) {
					std::cout << "퀘스트 발생!" << std::endl;
					npc.second.SetInDangerous(true);
					WQFS::GetInstance().MakeQuest(npc.second, WQFS::GetInstance().GetEvent(wEvent.first));
					std::cout << npc.second.getQuestNumber() << std::endl;
				}
			}
		}
		else {
			if ((std::get<1>(questList[npc.second.getQuestNumber()]) == 2 || std::get<1>(questList[npc.second.getQuestNumber()]) == 3) && questRemaining[npc.second.getQuestNumber()] <= 0) {
				std::cout << "장애물 제거 완료!" << std::endl;

				std::vector<Item> items = WQFS::GetInstance().CompleteQuest(npc.second, questCnt);

				for (auto& item : items) {
					inventory[item] += 1;
				}

				for (auto& item : inventory) {
					std::cout << item.first.GetName() << " : " << item.second << std::endl;
				}

				npc.second.ResetTimer();
			}
			
		}
	}

	for (auto& event : worldEvents) {
		if (event.second.getVisible() && event.second.GetType() == 0 && event.second.getHp() <= 0) {
			std::cout << "몬스터 처치 완료!" << std::endl;
			
			if (event.second.GetType() != -1) {
				for (auto& npc : WQFS::GetInstance().npcs) {
					if (npc.second.getQuestNumber() == event.second.getQuestNumber()) {
						std::vector<Item> c = WQFS::GetInstance().CompleteQuest(npc.second, questCnt);

						for (const auto& item : c) {
							inventory[item] += 1;
						}

						for (const auto& item : inventory) {
							std::cout << item.first.GetName() << " : " << item.second << std::endl;
						}

						npc.second.ResetTimer();
						std::cout << "끝" << npc.second.GetInDangerous() << std::endl;
						break;
					}
				}
			}
			event.second.setVisible(false);
		}
	}
}

void WQFS::CheckEvent() {
	if (!WQFS::GetInstance().isPaused) {
		for (auto& npc : WQFS::GetInstance().npcs) {
			if (!npc.second.GetCanDangerous()) {
				npc.second.Timer();
			}
		}
		for (auto& event : WQFS::GetInstance().worldEvents) {
			if (!event.second.GetIsCanCollid()) {
				event.second.Timer();
			}
			else {
				event.second.ResetTimer();
			}
		}
	}
}

void WQFS::Pause() {
	WQFS::GetInstance().pauseStart = clock();
	WQFS::GetInstance().isPaused = true;
}

void WQFS::Resume() {
	double pauseDuration;
	pauseDuration = (double)(clock() - WQFS::GetInstance().pauseStart) / CLOCKS_PER_SEC;

	for (auto& npc : WQFS::GetInstance().npcs) {
		npc.second.SetPauseDuration(pauseDuration);
	}

	for (auto& event : WQFS::GetInstance().worldEvents) {
		event.second.SetPauseDuration(pauseDuration);
	}
	WQFS::GetInstance().isPaused = false;
}

void WQFS::SetCompensation(NPC &npc, WorldEvent& event, int questType) {
	std::vector<Item> compList;
	bool isHp = false;
	bool isMp = false;
	bool isWeapon = false;
	bool isExchange = false;
	int allComp = 1;
	int random = (rand() % 100) / 10.0f;

	std::cout << "랜덤 값: " << random << std::endl;

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
			if ((isExchange && isHp) && random < 1.0f) {
				allComp = 2;

				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0 || comp.second.GetType() == 3) && comp.second.GetRarity() <= 1) {
						compList.push_back(comp.second);
						std::cout << "보상1" << std::endl;
					}
				}
			}
			else if (isExchange && random < 7.0f) {
				allComp = 1;
				for (const auto& comp : comps) {
					if (comp.second.GetType() == 3 && comp.second.GetRarity() <= 1) {
						compList.push_back(comp.second);
						std::cout << "보상2" << std::endl;
					}
				}
			}
			else if (isHp) {
				allComp = 1;
				for (const auto& comp : comps) {
					if (comp.second.GetType() == 0 && comp.second.GetRarity() <= 1) {
						compList.push_back(comp.second);
						std::cout << "보상3" << std::endl;
					}
				}
			}
			break;
		case 1:
			if ((isExchange && isMp && isHp) && random < 0.5f) {
				allComp = 3;

				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0 || comp.second.GetType() == 1 || comp.second.GetType() == 3) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (random < 1.5f) {
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
			else if (isHp && random < 4.0f) {
				allComp = 1;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isMp && random < 7.0f) {
				allComp = 1;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 1) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else  {
				allComp = 1;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 3) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			break;
		case 2:
			if ((isWeapon && isHp) && random < 1.0f) {
				allComp = 2;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0 || comp.second.GetType() == 2) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isWeapon && random < 7.0f) {
				allComp = 1;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 2) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			else if (isHp) {
				allComp = 1;
				for (const auto& comp : comps) {
					if ((comp.second.GetType() == 0) && comp.second.GetRarity() <= 3) {
						compList.push_back(comp.second);
					}
				}
			}
			break;
		case 3:
			if ((isExchange && isMp && isHp && isWeapon) && random < 0.5f) {
				allComp = 4;

				for (const auto& comp : comps) {
					compList.push_back(comp.second);
				}
			}
			else if (random < 2.0f) {
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
			else if (random < 5.0f) {
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
				allComp = 1;
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

	while (compList.size() > allComp) {
		compList.erase(compList.begin() + (rand() % compList.size()));
	}

	std::get<0>(questList[WQFS::GetInstance().questNumber]) = compList;
	std::get<1>(questList[WQFS::GetInstance().questNumber]) = questType;
	std::get<2>(questList[WQFS::GetInstance().questNumber]) = false;

	npc.setQuestNumber(WQFS::GetInstance().questNumber);
	event.setQuestNumber(WQFS::GetInstance().questNumber);

	WQFS::GetInstance().questNumber++;

	QuestTargetObjects.push_back(QuestTarget(&npc, &event));
}

std::vector<Item> WQFS::CompleteQuest(NPC &npc, int& questCnt)  {
	if (!std::get<2>(questList[npc.getQuestNumber()])) {
		int questNumber = npc.getQuestNumber();

		std::get<2>(questList[npc.getQuestNumber()]) = true;
		npc.SetInDangerous(false);
		++questCnt;

		for (auto& target : WQFS::GetInstance().QuestTargetObjects) {
			if (target.first->getQuestNumber() == npc.getQuestNumber()) {
				target.second->setQuestNumber(-1);
				break;
			}
		}

		npc.setQuestNumber(-1);

		std::cout << "퀘스트 완료!" << std::endl; 

		return std::get<0>(questList[questNumber]);
	}
	else {
		std::cout << "이미 완료한 퀘스트입니다!" << std::endl;
		return std::vector<Item>();
	}
}

std::vector<std::string> WQFS::GetQuestListByString(int maxQuestList) {
	std::vector<std::string> stringQuest;

	for (const auto quest : questList) {
		if (stringQuest.size() >= maxQuestList) {
			break;
		}

		std::string strData = "";
		for (const auto target : QuestTargetObjects) {
			if (target.first->getQuestNumber() != -1 && quest.first == target.first->getQuestNumber()) {
				strData = std::to_string(quest.first + 1) + ". "; 
				switch (std::get<1>(quest.second)) {
				case 0: strData += "Save NPC.";
					break;
				case 1: strData += "Retrieve  NPC's Item."; 
					break;
				case 2: strData += "Return the item to the NPC. (Remaining: " + std::to_string((WQFS::GetInstance().questRemaining[quest.first])) + ")";
					break;
				case 3: strData += "Remove obstacles for NPC (Remaining: " + std::to_string(WQFS::GetInstance().questRemaining[quest.first]) + ")";
					break;
				default: strData += "";  break;
				}
				break;
			}
		}

		if (strData != "") {
			stringQuest.push_back(strData);

			strData = std::get<0>(quest.second)[0].GetName();
			for (int i = 1; i < std::get<0>(quest.second).size(); ++i) {
				strData += "," + std::get<0>(quest.second)[i].GetName();
			}

			stringQuest.push_back(strData);
		}
	}

	if (stringQuest.size() > 0) {
		return stringQuest;
	}
	else {
		stringQuest.push_back("");
		return stringQuest;
	}
}

void WQFS::DiscountRemainingObstacles(int questNumber) {
	--questRemaining[questNumber];
}