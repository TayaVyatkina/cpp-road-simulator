#pragma once
#include "car.h"
namespace tests {
	void ConstructionCarTest();
	void TurningOnTest();
	void GoTest();

	void ConstructionRoadTest();
	void GettingDividerTest();
}

void CarTests() {
	using namespace tests;
	ConstructionCarTest();
	TurningOnTest();
}

void RoadTests() {
	using namespace tests;
	ConstructionRoadTest();
	GettingDividerTest();
}