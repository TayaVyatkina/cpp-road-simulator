#pragma once
namespace errors {
class CarDrivingError {
public:
    enum class Category {
        CrossingSolid,// пересечение сплошной
        DrivingIntoOncomingLane // выезд на встречную 
    };

    CarDrivingError(Category category);

    Category GetCategory() const;

    bool operator==(CarDrivingError rhs) const;

private:
    Category category_;
};
}