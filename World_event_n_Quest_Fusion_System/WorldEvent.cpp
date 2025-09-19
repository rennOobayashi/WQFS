#include "WorldEvent.h"

WorldEvent::WorldEvent(int _type, float pos_x, float pos_y)
	:type(_type), position_x(pos_x), position_y(pos_y) {}

void WorldEvent::DoEvent() {
	switch (type) {
		case 1:std::cout << "Monster";
			break;
		case 2:std::cout << "Earthquake";
			break;
		case 3:std::cout << "Landslide";
			break;
		case 4:std::cout << "Tsunami";
			break;
	}
}

std::string WorldEvent::getName() {
	switch (type) {
	case 1: return "괴물";
	case 2: return "지진";
	case 3: return "산사태";
	case 4: return "쓰나미";
	}
}

int WorldEvent::getType() {
	return type;
}