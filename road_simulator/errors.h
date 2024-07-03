#pragma once
#include <iostream>
#include <string>

namespace observer {

class CarDrivingError {
public:
    enum class Category {
          CrossingSolid// пересечение сплошной
        , DrivingAgainstDirectionOfMovement // выезд на встречную, движение задом
        , GetOffTheRoad // наезд на ограждение, в тупик
    };

    CarDrivingError(Category category);

    Category GetCategory() const;

    std::string ToString() const;

private:
    Category category_;
};

}//namespace observer 