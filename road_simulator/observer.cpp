#include "errors.h"
#include "observer.h"

namespace observer {

    TrafficLawsObserver::TrafficLawsObserver(std::ostream& out)
        :CarObserver()
        ,out_(out)
    {}

    void TrafficLawsObserver::OnRoadConditionsChanged(const road::Road& road, const car::Coords old_state, const car::Coords& new_state) const{
        try {
            if (IsCrossingSolid(old_state.line, new_state.line, road.GetDividerType(new_state.cell))) {
                throw observer::CarDrivingError(observer::CarDrivingError::Category::CrossingSolid);
            }
            if (IsDrivingIntoOncomingLane(old_state, new_state)) {
                throw observer::CarDrivingError(observer::CarDrivingError::Category::DrivingIntoOncomingLane);
            }
        }
        catch (observer::CarDrivingError& err) {
            out_ << err.ToString() << '\n';
        }
    }

    bool TrafficLawsObserver::IsCrossingSolid(const car::Line& old_side, const car::Line& new_side, const road::DividerType& divider) const {
        if (old_side != new_side) {// совершён переход на противоположную полосу
            return divider == road::DividerType::SOLID;
        }
        return false;
    }

    bool TrafficLawsObserver::IsDrivingIntoOncomingLane(const car::Coords& old_state, const car::Coords& new_state) const {
        if (old_state.cell != new_state.cell) {// движение по текущей полосе
            if (old_state.line == car::Line::RIGHT) {
                return old_state.cell > new_state.cell;
            }
            if (old_state.line == car::Line::LEFT) {
                return old_state.cell < new_state.cell;
            }
        }
        return false;
    }

    std::ostream& operator<<(std::ostream& output, CarDrivingError err) {
        output << std::string(err.ToString().length() + 2, '-') << '\n'
            << '|' << err.ToString() << '|' << '\n'
            << std::string(err.ToString().length() + 2, '-');
        return output;
    }

    CarDrivingError::CarDrivingError(Category category)
        :category_(std::move(category))
    {}

    CarDrivingError::Category CarDrivingError::GetCategory() const {
        return category_;
    }

    std::string CarDrivingError::ToString() const {
        using namespace std::literals;
        const static std::string CrossingSolid = "Crossing solid divider!"s;
        const static std::string DrivingIntoOncomingLane = "Driving into the oncoming lane!"s;
        switch (category_) {
        case Category::CrossingSolid:
            return CrossingSolid;
        case Category::DrivingIntoOncomingLane:
            return DrivingIntoOncomingLane;
        }
    }

}