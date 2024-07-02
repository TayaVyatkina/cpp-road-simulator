#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>

#include "car.h"
#include "console_drawer.h"
#include "observer.h"
#include "road.h"

namespace road_similator {

class ClicksHandler {
public:
    ClicksHandler() = delete;

    ClicksHandler(car::Car&, road::Road&, std::ostream&);

	void SimulateDriving();
private:
	car::Car& car_;
	road::Road& road_;
	drawer::ConsoleDrawer drawer_;
    observer::TrafficLawsObserver* observer_ = nullptr;
	std::ostream& out_;
};

}//namespace road_similator