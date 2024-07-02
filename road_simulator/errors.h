#pragma once
namespace errors {
class CarDrivingError {
public:
    enum class Category {
        CrossingSolid,// ����������� ��������
        DrivingIntoOncomingLane // ����� �� ��������� 
    };

    CarDrivingError(Category category);

    Category GetCategory() const;

    bool operator==(CarDrivingError rhs) const;

private:
    Category category_;
};
}