#pragma once
#include "road.h"
#include "car.h"
#include "console_drawer.h"

#include <windows.h>
#include <conio.h>
// agregation, фасад
namespace road_similator {
class ClicksHandler {
    ClicksHandler(car::Car& car, road::Road road)
		: car_(car)
		, road_(road)
		, drawer_(drawer::ConsoleDrawer(car, road))
	{}
	void SimulateDriving() {
		drawer_.DrawRoad();
		while (true) {
            if (_kbhit()) // слушатель нажатия
            {
                switch (_getch()) // ждёт нажатия без Enter
                {
                case 72: //up
                    car_.GoForward();
                    break;
                case 80: //down
                    car_.GoBackward();
                    break;
                case 75: //left
                    car_.TurnOnLeft();
                    break;
                case 77: //right
                    car_.TurnOnRight();
                    break;
                }
                drawer_.DrawRoad();//update picture
            }
		}
	}
private:
	car::Car& car_;
	road::Road road_;
	drawer::ConsoleDrawer drawer_;
};
}