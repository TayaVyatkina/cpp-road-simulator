#include "car.h"
#include <stdexcept>
namespace car {
	Coords::Coords(int cell, Line line, DirectionOfMov direction_of_mov) {
		if (cell >= 0) {
			this->cell = cell;
			this->line = line;
			this->direction_of_mov = direction_of_mov;
		}
		else {
			throw std::invalid_argument("negative \"cell\" value");
		}
	}

	Car::Car(Coords coords)
		:coords_(coords)
	{}

	Coords Car::GetCoords() const {
		return coords_;
	}

	void Car::GoForward() {
		if (coords_.direction_of_mov == DirectionOfMov::FORWARD) {
			++coords_.cell;
		}
		else if (coords_.direction_of_mov == DirectionOfMov::BACKWARD) {
			--coords_.cell;
		}
	}

	void Car::GoBackward() {
		if (coords_.direction_of_mov == DirectionOfMov::FORWARD) {
			--coords_.cell;
		}
		else if (coords_.direction_of_mov == DirectionOfMov::BACKWARD) {
			++coords_.cell;
		}
	}

	void Car::TurnOnRight() {
		int new_number_of_side = (static_cast<int>(coords_.direction_of_mov) + 1) % 4;
		coords_.direction_of_mov = static_cast<DirectionOfMov>(new_number_of_side);
	}

	void Car::TurnOnLeft() {
		int new_number_of_side = (static_cast<int>(coords_.direction_of_mov) + 3) % 4;
		coords_.direction_of_mov = static_cast<DirectionOfMov>(new_number_of_side);
	}
}