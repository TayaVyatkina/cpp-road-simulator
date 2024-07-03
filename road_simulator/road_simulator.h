#pragma once
#include <conio.h>
#include <iostream>
#include <memory>
#include <windows.h>

#include "car.h"
#include "console_drawer.h"
#include "observer.h"
#include "road.h"

namespace road_similator {

class ClicksHandler {
public:
    ClicksHandler() = delete;

	~ClicksHandler() = default;

    explicit ClicksHandler(car::Car&, road::Road&, std::ostream&);

	void SimulateDriving();

private:
	car::Car& car_;
	road::Road& road_;
	std::unique_ptr<drawer::ConsoleDrawer> drawer_;
    std::unique_ptr<observer::TrafficLawsObserver> observer_;
	std::ostream& out_;
};

}//namespace road_similator