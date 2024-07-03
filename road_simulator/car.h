#pragma once
namespace car {

enum class DirectionOfMov {
	// relative to the current side of the road
	FORWARD = 0,
	RIGHT,
	BACKWARD,
	LEFT
};

enum class Line {
	LEFT,
	RIGHT
};

struct Coords {
	Coords() = default;
	explicit Coords(int, Line, DirectionOfMov);

	int cell = 0;
	Line line = Line::RIGHT;
	DirectionOfMov direction_of_mov = DirectionOfMov::FORWARD;
};

class Car {
public:
	Car() = default;

	explicit Car(Coords);

	Coords GetCoords() const;

	void SetCoords(const Coords&);

	void GoForward();

	void GoBackward();

	void TurnOnRight();

	void TurnOnLeft();

private:
	Coords coords_;
};

}// namespace car 