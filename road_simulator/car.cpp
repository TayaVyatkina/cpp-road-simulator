#include <iostream>
#include <stdexcept>

#include "car.h"

namespace car {

Coords::Coords(int cell, Line line, DirectionOfMov direction_of_mov)
	: cell(cell)
	, line(line)
	, direction_of_mov(direction_of_mov)
{}

Car::Car(Coords coords)
	:coords_(coords)
{}

Coords Car::GetCoords() const {
	return coords_;
}

void Car::SetCoords(const Coords& new_coords) {
	coords_ = new_coords;
}

void Car::GoForward() {
	if (coords_.direction_of_mov == DirectionOfMov::FORWARD) {
		++coords_.cell;
	}
	else if (coords_.direction_of_mov == DirectionOfMov::BACKWARD) {
		--coords_.cell;
	}
	else if (coords_.direction_of_mov == DirectionOfMov::LEFT) {
		if (coords_.line == Line::RIGHT) {
			coords_.line = Line::LEFT;
		}
	}
	else if (coords_.direction_of_mov == DirectionOfMov::RIGHT) {
		if (coords_.line == Line::LEFT) {
			coords_.line = Line::RIGHT;
		}
	}		
}

void Car::GoBackward() {
	if (coords_.direction_of_mov == DirectionOfMov::FORWARD) {
		--coords_.cell;
	}
	else if (coords_.direction_of_mov == DirectionOfMov::BACKWARD) {
		++coords_.cell;
	}
	else if (coords_.direction_of_mov == DirectionOfMov::RIGHT) {
		if (coords_.line == Line::RIGHT) {
			coords_.line = Line::LEFT;
		}
	}
	else if (coords_.direction_of_mov == DirectionOfMov::LEFT) {
		if (coords_.line == Line::LEFT) {
			coords_.line = Line::RIGHT;
		}
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

}// namespace car