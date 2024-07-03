#pragma once

namespace tests {
	void ConstructionCarTest();
	void TurningOnTest();
	void GoTest();

	void ConstructionRoadTest();
	void GettingDividerTest();

	void DrawRoadTest();

	void ConstructSimulatorTest();
	void ObserverTest();
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

	GoTest();
}

void DrawerTests() {
	using namespace tests;
	DrawRoadTest();
}
void SimulationTest() {
	using namespace tests;
	ObserverTest();
	ConstructSimulatorTest();
	
}
