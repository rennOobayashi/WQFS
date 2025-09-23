#include "WQFS.h"

WQFS::WQFS(int _fame) : fame(_fame) {
	init();
}

WQFS::~WQFS() {
	world_events.clear();
	npcs.clear();
	comps.clear();
}

void WQFS::init() {
	world_events.push_back(WorldEvent(1, 0, 0));
	world_events.push_back(WorldEvent(2, 0, 0));
	world_events.push_back(WorldEvent(3, 0, 0));
	world_events.push_back(WorldEvent(4, 0, 0));

	npcs.push_back(NPC("일반인", 1, 0, 0));
	npcs.push_back(NPC("아이템 상인", 2, 0, 0));
	npcs.push_back(NPC("무기 상인", 3, 0, 0));
	npcs.push_back(NPC("행상인", 4, 0, 0));

	comps.push_back(Item("음식", 1, 5));
	comps.push_back(Item("포션", 1, 11));
	comps.push_back(Item("날카로운 검", 2, 2));
	comps.push_back(Item("기사의 검", 2, 3));

	start_time = clock();
	time_limit = 3;
}

void WQFS::Test() {
	start_time = clock();

	while (true) {
		clock_t now = clock();

		double my_timer = double(now - start_time) / CLOCKS_PER_SEC;

		if (time_limit <= my_timer) {
			int rand_npc = (rand() % 4);
			int rand_event = (rand() % 4);
			
			std::cout << "현재 " << world_events[rand_event].getName() <<
				"로 인해 " << npcs[rand_npc].getName() << "가 위험에 빠졌습니다." << std::endl;
			
			std::cout << "보상 (";
			switch (rand_npc) {
			case 0: std::cout << comps[rand() % 3].getName();
				break;
			case 1: std::cout << comps[1].getName();
				break;
			case 2: std::cout << comps[(rand() % 2) + 2].getName();
				break;
			case 3: std::cout << comps[rand() % 4].getName() << ", " << comps[rand() % 4].getName();
				break;
			}
			std::cout << ")" << std::endl;

			start_time = clock();
		}
	}
}