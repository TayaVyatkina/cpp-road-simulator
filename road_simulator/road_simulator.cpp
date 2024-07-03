#include <iostream>

#include "errors.h"
#include "road_simulator.h"

namespace road_similator {

ClicksHandler::ClicksHandler(car::Car& car, road::Road& road, std::ostream& out = std::cout)
    : car_(car)
    , road_(road)
    , drawer_(std::make_unique<drawer::ConsoleDrawer>(car, road))
    , observer_(std::make_unique<observer::TrafficLawsObserver>(out))
    , out_(out)
{}

void ClicksHandler::SimulateDriving() {
    (*drawer_).DrawRoad(out_);
    while (true) {
        if (_kbhit()) // слушатель нажатия
        {
            auto old_state = car_.GetCoords();
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

            //update picture
            (*drawer_).DrawRoad(out_);

            // check rules compliance
            try {
                (*observer_).OnRoadConditionsChanged(road_
                    , old_state/* old_state*/
                    , car_.GetCoords());/* new_state*/         
            }
            catch (observer::CarDrivingError& err) {      
                // return a state that does not extend beyond the road
                if (err.GetCategory() == observer::CarDrivingError::Category::GetOffTheRoad) {
                    car_.SetCoords(old_state);
                }
            }       
        }
    }
}

}//namespace road_similator 