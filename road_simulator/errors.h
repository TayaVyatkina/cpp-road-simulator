#pragma once
#include <iostream>
#include <string>

namespace observer {

class CarDrivingError {
public:
    enum class Category {
          CrossingSolid
        , DrivingAgainstDirectionOfMovement
        , GetOffTheRoad
    };

    CarDrivingError(Category category);

    Category GetCategory() const;

    std::string ToString() const;

private:
    Category category_;
};

}//namespace observer 