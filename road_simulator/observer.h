#pragma once
#include <iostream>

#include "car.h"
#include "road.h"

namespace observer {

class CarObserver {
public:
    CarObserver() = default;

    virtual void OnRoadConditionsChanged(const road::Road&, const car::Coords, const car::Coords&) const = 0;

protected:
    ~CarObserver() = default;
};

class TrafficLawsObserver : public CarObserver {
public:
    TrafficLawsObserver(std::ostream&);

    void OnRoadConditionsChanged(const road::Road& road, const car::Coords old_state, const car::Coords& new_state) const override;

private:
    bool IsCrossingSolid(const car::Line& old_side, const car::Line& new_side, const road::DividerType& divider) const;

    bool IsDrivingIntoOncomingLane(const car::Coords& old_state, const car::Coords& new_state) const;

    std::ostream& out_;
};

}//namespace observer 
