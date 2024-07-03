#pragma once
#include <iostream>

#include "car.h"
#include "road.h"

namespace drawer {

class ConsoleDrawer {
public:
	ConsoleDrawer(car::Car&, road::Road&);

	void DrawRoad(std::ostream&);

private:
	void PrintEdge(std::ostream&);

	void PrintDivider(std::ostream&, size_t);

	void PrintEmpty(std::ostream&);

	void PrintEmptyRoadSection(std::ostream&, size_t);

	void PrintSectionWithCar(std::ostream&);

	void PrintCar(std::ostream&);
	 
	void PrintFence(std::ostream&);

	car::Car& car_;
	road::Road& road_;
};
}// namespace drawer 