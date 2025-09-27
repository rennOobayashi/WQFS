#include "WQFS.h"


bool RandomInRange(int prob) {
	srand((unsigned int)time(NULL));

	int random = (rand() % 100) + 1;

	std::cout << random << " " << prob << " " << (random > prob) << std::endl;

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
	WQFS::GetInstance().SetCompensation(npcType);

	std::cout << "Compensation: " << WQFS::GetInstance().GetCompensation() << std::endl;

	switch (eventType) {
	case 0: WQFS().MonsterEvent(npcType);
		break;
	case 1: WQFS().StaticEvent(npcType);
		break;
	case 2: WQFS().MonsterEvent(npcType);
		break;
	default: std::cout << "Wrong event type!" << std::endl;
		break;
	}
}

//HP = 1(1), MP = 2(10), Weapon = 4(100), Collectible = 8(1000), HP and Collectible = 9(1001)
//NPC 0 (HP(30), Collectible(60), All(10))
//NPC 1 (HP(40), MP(30), Collectible Item(15), Both(10), All(5))
//NPC 2 (Weapon type Item(60), HP(20), Both(15), All(5))
//NPC 3 All(One(50), Two(30), Three(15), All(5))

void WQFS::SetCompensation(int npcType) {
	bool isHp = false;
	bool isMp = false;
	bool isWeapon = false;
	bool isCollectible = false;

	for (const auto& comp : comps) {
		if (isHp && isMp && isWeapon && isCollectible) {
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
		else if (!isCollectible && comp.second.GetType() == 3) {
			isCollectible = true;
			continue;
		}

	}

	switch (npcType) {
		case 0:
			if ((isCollectible && isHp) && RandomInRange(10)) { // 1001
				compensation = 9;
			}
			else if (isCollectible && RandomInRange(60)) { //1000
				compensation = 8;
			}
			else if (isHp) { //0001
				compensation = 1;
			}
			break;
		case 1:
			if ((isCollectible && isMp && isHp) && RandomInRange(5)) { //1011
				compensation = 11;
			}
			else if (RandomInRange(10)) {
				if ((isCollectible && isHp)) { //1001
					compensation = 9;
				}
				else if ((isCollectible && isMp)) { //1010
					compensation = 10;
				}
				else { //0011
					compensation = 3;
				}
			}
			else if (isHp && RandomInRange(40)) { //0001
				compensation = 1;
			}
			else if (isMp && RandomInRange(30)) { //0010
				compensation = 2;
			}
			else  { //1000
				compensation = 8;
			}
			break;
		case 2:
			if ((isWeapon && isHp) && RandomInRange(10)) { //0101
				compensation = 5;
			}
			else if (isWeapon && RandomInRange(60)) { //0100
				compensation = 4;
			}
			else if (isHp) { //0001
				compensation = 1;
			}
			break;
		case 3:
			if ((isCollectible && isMp && isHp && isWeapon) && RandomInRange(5)) { //1111
				compensation = 15;
			}
			else if (RandomInRange(15)) { 
				if ((isCollectible && isMp && isWeapon)) { //1110
					compensation = 14;
				}
				else if ((isCollectible && isHp && isWeapon)) { //1101
					compensation = 13;
				}
				else if ((isCollectible && isHp && isMp)) { //1011
					compensation = 11;
				}
				else if ((isMp && isHp && isWeapon)) { //0111
					compensation = 7;
				}
			}
			else if (RandomInRange(30)) {
				if ((isCollectible && isHp)) { //1001
					compensation = 9;
				}
				else if ((isCollectible && isWeapon)) { //1100
					compensation = 12;
				}
				else if ((isCollectible && isMp)) { //1010
					compensation = 10;
				}
				else if ((isCollectible && isWeapon)) { //1100
					compensation = 12;
				}
				else if ((isWeapon && isMp)) { //0110
					compensation = 11;
				}
				else if ((isHp && isWeapon)) { //0101
					compensation = 7;
				}
				else if ((isHp && isMp)) { //0011
					compensation = 7;
				}
			}
			else {
				if ((isCollectible) && RandomInRange(25)) { //1000
					compensation = 8;
				}
				else if ((isWeapon) && RandomInRange(25)) { //0100
					compensation = 4;
				}
				else if ((isMp) && RandomInRange(25)) { //0010
					compensation = 2;
				}
				else { //0001
					compensation = 1;
				}
			}
			break;
		default: std::cout << "Wrong NPC type!" << std::endl;
			break;
	}

	std::cout << "Set compensation to " << compensation << std::endl;
}
int WQFS::GetCompensation()  {
	return compensation;
}

void WQFS::MonsterEvent(int npcType)  {

}

void WQFS::DynamicEvent(int npcType)  {

}

void WQFS::StaticEvent(int npcType)  {

}