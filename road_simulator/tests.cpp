#include "car.h"
#include "road.h"
#include "observer.h"
#include "road_simulator.h"
#include "errors.h"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;
namespace tests {
	using namespace car;
	using namespace road;
	using namespace drawer;
	using namespace observer;
	using namespace road_similator;

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
		{//  negative car coords			
			Coords start_position{ -10 , Line::LEFT, DirectionOfMov::FORWARD };
			Car test_car(start_position);
			assert(test_car.GetCoords() == start_position);
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

	void GoTest() {
		{// go forward
			Car test_car;
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoForward();
			assert(test_car.GetCoords() == Coords(1, Line::RIGHT, DirectionOfMov::FORWARD));
		}
		{// go backward
			Car test_car(Coords{ 1, Line::RIGHT, DirectionOfMov::FORWARD });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoBackward();
			assert(test_car.GetCoords() == Coords(0, Line::RIGHT, DirectionOfMov::FORWARD));
		}
		{// right line, go right
			Car test_car(Coords{ 0, Line::RIGHT, DirectionOfMov::RIGHT });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoForward();
			assert(test_car.GetCoords() == Coords(0, Line::RIGHT, DirectionOfMov::RIGHT));
		}
		{// right line, go left
			Car test_car(Coords{ 0, Line::RIGHT, DirectionOfMov::LEFT });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoForward();
			assert(test_car.GetCoords() == Coords(0, Line::LEFT, DirectionOfMov::LEFT));
		}
		{// left line, go left
			Car test_car(Coords{ 0, Line::LEFT, DirectionOfMov::LEFT });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoForward();
			assert(test_car.GetCoords() == Coords(0, Line::LEFT, DirectionOfMov::LEFT));
		}
		{// left line, go right
			Car test_car(Coords{ 0, Line::LEFT, DirectionOfMov::RIGHT });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoForward();
			assert(test_car.GetCoords() == Coords(0, Line::RIGHT, DirectionOfMov::RIGHT));
		}
		{// right line, turn left, go backward
			Car test_car(Coords{ 0, Line::RIGHT, DirectionOfMov::LEFT });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoBackward();
			assert(test_car.GetCoords() == Coords(0, Line::RIGHT, DirectionOfMov::LEFT));
		}
		{// right line, turn right, go backward
			Car test_car(Coords{ 0, Line::RIGHT, DirectionOfMov::RIGHT });
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);

			test_car.GoBackward();
			assert(test_car.GetCoords() == Coords(0, Line::LEFT, DirectionOfMov::RIGHT));
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

	void DrawRoadTest() {
		{// empty road
			Car test_car;
			Road test_road;
			ConsoleDrawer test_drawer(test_car, test_road);
			std::ostringstream out;
			test_drawer.DrawRoad(out);
			assert(out.str() == "");
		}
		{// default state, road shorter than printing
			Car test_car;
			Road test_road;
			test_road.AddSection(5, DividerType::SOLID);
			test_road.AddSection(3, DividerType::DOTTED);
			ConsoleDrawer test_drawer(test_car, test_road);
			std::ostringstream out;
			std::ostringstream right_out;
			right_out
				<< "     |###|\n"
				<< "    7| : |\n"
				<< "    6| : |\n"
				<< "    5| : |\n"
				<< "    4| | |\n"
				<< "    3| | |\n"
				<< "    2| | |\n"
				<< "    1| | |\n"
				<< "    0| |^|\n"
				<< "     |###|\n";
			test_drawer.DrawRoad(out);
			assert(out.str() == right_out.str());
		}
		{// default state, road longer than printing
			Car test_car;
			Road test_road;
			test_road.AddSection(7, DividerType::SOLID);
			test_road.AddSection(3, DividerType::DOTTED);
			test_road.AddSection(1, DividerType::SOLID);
			ConsoleDrawer test_drawer(test_car, test_road);
			std::ostringstream out;
			std::ostringstream right_out;
			right_out
				<< "    9| : |\n"
				<< "    8| : |\n"
				<< "    7| : |\n"
				<< "    6| | |\n"
				<< "    5| | |\n"
				<< "    4| | |\n"
				<< "    3| | |\n"
				<< "    2| | |\n"
				<< "    1| | |\n"
				<< "    0| |^|\n"
				<< "     |###|\n";
			test_drawer.DrawRoad(out);
			assert(out.str() == right_out.str());
		}
		{// crushing the fence in the end
			Car test_car(Coords{ -1 , Line::RIGHT, DirectionOfMov::FORWARD });
			Road test_road;
			test_road.AddSection(1, DividerType::SOLID);
			ConsoleDrawer test_drawer(test_car, test_road);
			std::ostringstream out;
			std::ostringstream right_out;
			right_out
				<< "     |###|\n"
				<< "    0| |^|\n"
				<< "     |###|\n";
			test_drawer.DrawRoad(out);
			assert(out.str() == right_out.str());
		}
		{// crushing the fence on the start
			Car test_car(Coords{ 1 , Line::LEFT, DirectionOfMov::FORWARD });
			Road test_road;
			test_road.AddSection(1, DividerType::SOLID);
			ConsoleDrawer test_drawer(test_car, test_road);
			std::ostringstream out;
			std::ostringstream right_out;
			right_out
				<< "     |###|\n"
				<< "    0|^| |\n"
				<< "     |###|\n";
			test_drawer.DrawRoad(out);
			assert(out.str() == right_out.str());
		}
	}
	
	void ObserverTest() {
		{// driving into the oncoming lane
			Road test_road;
			test_road.AddSection(2, DividerType::SOLID);
			std::ostringstream message_out;
			TrafficLawsObserver observer(message_out);
			Coords old_state(1, Line::RIGHT, DirectionOfMov::FORWARD);
			Coords new_state(0, Line::RIGHT, DirectionOfMov::FORWARD);

			observer.OnRoadConditionsChanged(test_road, old_state, new_state);
			observer::CarDrivingError right_error(observer::CarDrivingError::Category::DrivingAgainstDirectionOfMovement);
			std::ostringstream right_answer;
			right_answer << right_error.ToString() << '\n';
			assert(message_out.str() == right_answer.str());
		}
		{// get off the road, start
			Road test_road;
			test_road.AddSection(1, DividerType::SOLID);
			std::ostringstream message_out;
			TrafficLawsObserver observer(message_out);
			Coords old_state(0, Line::RIGHT, DirectionOfMov::FORWARD);
			Coords new_state(1, Line::RIGHT, DirectionOfMov::FORWARD);
			bool is_catching = false;
			try {
				observer.OnRoadConditionsChanged(test_road, old_state, new_state);
			}
			catch (observer::CarDrivingError& err) {
				is_catching = true;
				observer::CarDrivingError right_error(observer::CarDrivingError::Category::GetOffTheRoad);
				std::ostringstream right_answer;
				right_answer << right_error.ToString() << '\n';
				assert(message_out.str() == right_answer.str());
			}
			assert(is_catching = true);
		}
		{// get off the road, finish
			Road test_road;
			test_road.AddSection(1, DividerType::SOLID);
			std::ostringstream message_out;
			TrafficLawsObserver observer(message_out);
			Coords old_state(0, Line::LEFT, DirectionOfMov::BACKWARD);
			Coords new_state(-1, Line::LEFT, DirectionOfMov::BACKWARD);

			bool is_catching = false;
			try {
				observer.OnRoadConditionsChanged(test_road, old_state, new_state);
			}
			catch (observer::CarDrivingError& err) {
				is_catching = true;
				observer::CarDrivingError right_error(observer::CarDrivingError::Category::GetOffTheRoad);
				std::ostringstream right_answer;
				right_answer << right_error.ToString() << '\n';
				assert(message_out.str() == right_answer.str());
			}
			assert(is_catching = true);
		}
		{// turning left
			Road test_road;
			test_road.AddSection(2, DividerType::DOTTED);
			std::ostringstream message_out;
			TrafficLawsObserver observer(message_out);
			Coords old_state(0, Line::RIGHT, DirectionOfMov::LEFT);
			Coords turn_state(0, Line::LEFT, DirectionOfMov::LEFT);
			Coords new_state(0, Line::LEFT, DirectionOfMov::BACKWARD);

			observer.OnRoadConditionsChanged(test_road, old_state, turn_state);		
			observer.OnRoadConditionsChanged(test_road, turn_state, new_state);
			assert(message_out.str() == "Turning\nSuccessful turning\n");
		}
		{// turning right
			Road test_road;
			test_road.AddSection(2, DividerType::DOTTED);
			std::ostringstream message_out;
			TrafficLawsObserver observer(message_out);
			Coords old_state(0, Line::LEFT, DirectionOfMov::RIGHT);
			Coords turn_state(0, Line::RIGHT, DirectionOfMov::RIGHT);
			Coords new_state(0, Line::RIGHT, DirectionOfMov::FORWARD);

			observer.OnRoadConditionsChanged(test_road, old_state, turn_state);
			observer.OnRoadConditionsChanged(test_road, turn_state, new_state);
			assert(message_out.str() == "Turning\nSuccessful turning\n");
		}
		{// crossing solid
			Road test_road;
			test_road.AddSection(2, DividerType::SOLID);
			std::ostringstream message_out;
			TrafficLawsObserver observer(message_out);
			Coords old_state(0, Line::RIGHT, DirectionOfMov::LEFT);
			Coords new_state(0, Line::LEFT, DirectionOfMov::LEFT);

			observer.OnRoadConditionsChanged(test_road, old_state, new_state);
			observer::CarDrivingError right_error(observer::CarDrivingError::Category::CrossingSolid);
			std::ostringstream right_answer;
			right_answer << right_error.ToString() << '\n' << "Turning\n";
			assert(message_out.str() == right_answer.str());
		}
	}

	void ConstructSimulatorTest() {
		{// default state, road shorter than printing
			Car test_car(Coords{ 0, Line::LEFT, DirectionOfMov::FORWARD });
			Road test_road;
			test_road.AddSection(7, DividerType::SOLID);
			test_road.AddSection(7, DividerType::DOTTED);
			observer::TrafficLawsObserver observer(cout);
			ClicksHandler ch(test_car, test_road, cout);
			ch.SimulateDriving();
		}
	}

}