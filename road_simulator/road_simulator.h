#pragma once
#include "road.h"
#include "car.h"
#include "console_drawer.h"
#include "observer.h"

#include <windows.h>
#include <conio.h>
// agregation, Фасад
namespace road_similator {
class ClicksHandler {
public:
    ClicksHandler() = delete;

    ClicksHandler(car::Car& car, road::Road& road);

	void SimulateDriving();
private:
	car::Car& car_;
	road::Road& road_;
	drawer::ConsoleDrawer drawer_;
    observer::TrafficLawsObserver* observer_ = nullptr;
};
}