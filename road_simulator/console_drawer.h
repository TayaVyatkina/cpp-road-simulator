#pragma once
#include "road.h"
#include "car.h"

#include <iostream>
// composition
namespace drawer {
class ConsoleDrawer {
public:
	ConsoleDrawer(car::Car& car, road::Road road);

	void DrawRoad(std::ostream& out = std::cout);

private:
	void PrintEdge(std::ostream& out);

	void PrintDivider(std::ostream& out, size_t row);

	void PrintEmptyRoadSection(std::ostream& out);

	void PrintSectionWithCar(std::ostream& out);

	void PrintCar(std::ostream& out);

	car::Car& car_;
	road::Road road_;
};
}