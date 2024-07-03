#pragma once
#include <iostream>

#include "car.h"
#include "road.h"

namespace observer {

// basic abstract class for constructing different observers
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

    void OnRoadConditionsChanged(const road::Road&, const car::Coords, const car::Coords&) const override;

private:
    bool IsCrossingSolid(const car::Line&, const car::Line&, const road::DividerType&) const;

    bool IsDrivingAgainstDirectionOfMovement(const car::Coords&, const car::Coords&) const;

    bool IsGetOffTheRoad(const car::Coords&, const size_t) const;

    bool IsTurning(const car::Coords&, const car::Coords&) const;

    bool IsFinishTurning(const car::Coords&, const car::Coords&) const;

    std::ostream& out_;
};

}//namespace observer 
