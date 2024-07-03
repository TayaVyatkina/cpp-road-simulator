#include "errors.h"
#include "observer.h"

namespace observer {

    TrafficLawsObserver::TrafficLawsObserver(std::ostream& out)
        :CarObserver()
        ,out_(out)
    {}

    void TrafficLawsObserver::OnRoadConditionsChanged(const road::Road& road, const car::Coords old_state, const car::Coords& new_state) const{
        try {
            if (IsDrivingAgainstDirectionOfMovement(old_state, new_state)) {
                throw observer::CarDrivingError(observer::CarDrivingError::Category::DrivingAgainstDirectionOfMovement);
            }
        }
        catch (observer::CarDrivingError& err) {
            out_ << err.ToString() << '\n';
        }
        try {
            if (IsGetOffTheRoad(new_state, road.GetLength())) {
                throw observer::CarDrivingError(observer::CarDrivingError::Category::GetOffTheRoad);
            }
        }
        catch(observer::CarDrivingError& err){
            out_ << err.ToString() << '\n';
            throw err;
        }

        try {
            if (IsCrossingSolid(old_state.line, new_state.line, road.GetDividerType(new_state.cell))) {
                throw observer::CarDrivingError(observer::CarDrivingError::Category::CrossingSolid);
            }
        }
        catch (observer::CarDrivingError& err) {
            out_ << err.ToString() << '\n';
        }
 
        // check right turning    
        if (IsTurning(old_state, new_state)) {
            out_ << "Turning\n";
        }
        if (IsFinishTurning(old_state, new_state)) {
            out_ << "Successful turning\n";
        }
    }

    bool TrafficLawsObserver::IsTurning(const car::Coords& old_state, const car::Coords& new_state) const {
        return old_state.line != new_state.line; 
    }

    bool TrafficLawsObserver::IsFinishTurning(const car::Coords& old_state, const car::Coords& new_state) const {
        if (old_state.line == new_state.line && old_state.cell == new_state.cell) {
            if (old_state.line == car::Line::LEFT) {
                return old_state.direction_of_mov != car::DirectionOfMov::BACKWARD && new_state.direction_of_mov == car::DirectionOfMov::BACKWARD;
            }
            else {// ar::Line::RIGHT
                return old_state.direction_of_mov != car::DirectionOfMov::FORWARD && new_state.direction_of_mov == car::DirectionOfMov::FORWARD;
            }
        }
        return false;
    }

    bool TrafficLawsObserver::IsCrossingSolid(const car::Line& old_side, const car::Line& new_side, const road::DividerType& divider) const {
        if (old_side != new_side) {// совершён переход на противоположную полосу
            return divider == road::DividerType::SOLID;
        }
        return false;
    }

    bool TrafficLawsObserver::IsDrivingAgainstDirectionOfMovement(const car::Coords& old_state, const car::Coords& new_state) const {
        if (old_state.line == new_state.line && old_state.cell != new_state.cell) {
            if (old_state.line == car::Line::RIGHT) {
                return old_state.cell > new_state.cell || old_state.direction_of_mov == car::DirectionOfMov::BACKWARD;
            }
            if (old_state.line == car::Line::LEFT) {
                return old_state.cell < new_state.cell || old_state.direction_of_mov == car::DirectionOfMov::FORWARD;
            }
        }
        return false;
    }

    bool TrafficLawsObserver::IsGetOffTheRoad(const car::Coords& new_side, const size_t len) const{
        return new_side.cell >= len || new_side.cell <= -1;
    }


    // Class CarDrivingError

    CarDrivingError::CarDrivingError(Category category)
        :category_(std::move(category))
    {}

    CarDrivingError::Category CarDrivingError::GetCategory() const {
        return category_;
    }

    std::string CarDrivingError::ToString() const {
        using namespace std::literals;
        const static std::string CrossingSolid = "Crossing solid divider!"s;
        const static std::string DrivingAgainstDirectionOfMovement = "Driving against the direction of movement!"s;
        const static std::string GetOffTheRoad = "Crash into the fence!"s;

        switch (category_) {
        case Category::CrossingSolid:
            return CrossingSolid;
        case Category::DrivingAgainstDirectionOfMovement:
            return DrivingAgainstDirectionOfMovement;
        case Category::GetOffTheRoad:
            return GetOffTheRoad;
        }
    }

}// namespace observer 