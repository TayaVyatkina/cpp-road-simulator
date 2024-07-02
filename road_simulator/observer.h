#pragma once
#include "road.h"
#include "car.h"
#include "errors.h"

namespace observer {
class CarObserver {
public:
    CarObserver() = default;
    virtual void OnRoadConditionsChanged(const car::Car&, const road::Road&) = 0;

protected:
    ~CarObserver() = default;
};

class TrafficLawsObserver : public CarObserver {
public:
    TrafficLawsObserver()
        :CarObserver()
    {}
    void OnRoadConditionsChanged(const car::Car& car, const road::Road& road) override {
        CheckCrossingSolid();
        CheckDrivingIntoOncomingLane();
    }
private:
    void CheckCrossingSolid(){}
    void CheckDrivingIntoOncomingLane(){}
};
}
