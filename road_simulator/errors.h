#pragma once
#include <iostream>
#include <string>

namespace observer {

class CarDrivingError {
public:
    enum class Category {
        CrossingSolid,// пересечение сплошной
        DrivingIntoOncomingLane // выезд на встречную 
    };

    CarDrivingError(Category category);

    Category GetCategory() const;

    std::string ToString() const;

private:
    Category category_;
};

}//namespace observer 