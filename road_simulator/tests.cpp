
#include "car.h"
#include "road.h"

#include <cassert>
#include <stdexcept>
#include <iostream>
using namespace std;
namespace tests {
	using namespace car;
	using namespace road;

	bool operator==(const Coords & lhs, const Coords & rhs) {
		return lhs.line == rhs.line && lhs.cell == rhs.cell;
	}

	void ConstructionCarTest() {
		{// empty car
			Car test_car;
			Coords start_position{ 0 , Line::RIGHT, DirectionOfMov::FORWARD };
			assert(test_car.GetCoords() == start_position);
		}
		{// no-empty car
			Coords start_position{ 10 , Line::LEFT, DirectionOfMov::FORWARD };
			Car test_car(start_position);
			assert(test_car.GetCoords() == start_position);
		}
		{//  wrong car coords			
			bool is_error_catch = false;
			try {
				Coords start_position{ -10, Line::LEFT, DirectionOfMov::FORWARD };
				//Car test_car(start_position);
			}
			catch (const std::invalid_argument& err) {
				is_error_catch = true;
			}
			if (!is_error_catch) {
				throw std::invalid_argument("negative \"cell\" value");
			}
		}
	}

	void TurningOnTest() {
		{// turning right
			Car test_car(Coords{});
			test_car.TurnOnRight();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::RIGHT);
			test_car.TurnOnRight();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::BACKWARD);
			test_car.TurnOnRight();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::LEFT);
			test_car.TurnOnRight();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::FORWARD);
		}
		{// turning left
			Car test_car(Coords{});
			test_car.TurnOnLeft();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::LEFT);
			test_car.TurnOnLeft();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::BACKWARD);
			test_car.TurnOnLeft();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::RIGHT);
			test_car.TurnOnLeft();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::FORWARD);
		}
		{// turning left/right
			Car test_car(Coords{ 0, Line::RIGHT, DirectionOfMov::LEFT });
			test_car.TurnOnLeft();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::BACKWARD);
			test_car.TurnOnRight();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::LEFT);
			test_car.TurnOnRight();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::FORWARD);
			test_car.TurnOnLeft();
			assert(test_car.GetCoords().direction_of_mov == DirectionOfMov::LEFT);
		}
		{// more turning
			Car test_car(Coords{});
			for (size_t i = 1; i < 10; ++i) {
				test_car.TurnOnRight();
				assert(test_car.GetCoords().direction_of_mov == static_cast<DirectionOfMov>(i % 4));
			}
		}
	}

	void GoTest() {}


	void ConstructionRoadTest(){
		{// empty road
			Road test_road;
			assert(test_road.GetLength() == 0);

			// add empty section
			test_road.AddSection(0, DividerType::SOLID);
			assert(test_road.GetLength() == 0);

			// add non-empty section
			test_road.AddSection(5, DividerType::SOLID);
			assert(test_road.GetLength() == 5);

			// add non-empty section
			test_road.AddSection(3, DividerType::DOTTED);
			assert(test_road.GetLength() == 8);

		}
	}

	void GettingDividerTest(){
		Road test_road;		
		test_road.AddSection(5, DividerType::SOLID);
		test_road.AddSection(3, DividerType::DOTTED);

		//get right section
		assert(test_road.GetDividerType(0) == DividerType::SOLID);

		//get out of range section
		//road_[7] is last
		bool is_error_catch = false;
		try {
			test_road.GetDividerType(8);
		}
		catch (const std::out_of_range& err) {
			is_error_catch = true;
		}
		if (!is_error_catch) {
			throw std::out_of_range("trying to get value out of \"road_\"");
		}
	}

}