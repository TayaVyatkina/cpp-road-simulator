#include "road_simulator.h"
namespace road_similator {
    ClicksHandler::ClicksHandler(car::Car& car, road::Road& road)
        : car_(car)
        , road_(road)
        , drawer_(drawer::ConsoleDrawer(car, road))
        , observer_(new observer::TrafficLawsObserver())
    {}

    void ClicksHandler::SimulateDriving() {
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
                (*observer_).OnRoadConditionsChanged(car_, road_);
                drawer_.DrawRoad();//update picture
            }
        }
    }
}