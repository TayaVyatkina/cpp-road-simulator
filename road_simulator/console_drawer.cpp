#include "iomanip"

#include "console_drawer.h"

namespace drawer {
	ConsoleDrawer::ConsoleDrawer(car::Car& car, road::Road road)
		: car_(car)
		, road_(road)
	{}

	void ConsoleDrawer::DrawRoad(std::ostream& out) {
		system("cls");
		int len_of_view_section = std::min(static_cast<int>(car_.GetCoords().cell) + 9, static_cast<int>(road_.GetLength()) - 1);
		if (len_of_view_section > 0) {
			for (int row = len_of_view_section; row > static_cast<int>(car_.GetCoords().cell); --row) {
				out << std::setw(5) << row;// cell number
				PrintEdge(out);
				PrintEmptyRoadSection(out);
				PrintDivider(out, row);
				PrintEmptyRoadSection(out);
				PrintEdge(out);
				out << std::endl;
			}
			PrintSectionWithCar(out);
		}
	}

	void ConsoleDrawer::PrintEdge(std::ostream& out) {
		out << static_cast<char>(124);
	}

	void ConsoleDrawer::PrintDivider(std::ostream& out, size_t row) {
		out << (road_.GetDividerType(row) == road::DividerType::DOTTED ? static_cast<char>(58) : static_cast<char>(124));
	}

	void ConsoleDrawer::PrintEmptyRoadSection(std::ostream& out) {
		out << " ";
	}

	void ConsoleDrawer::PrintSectionWithCar(std::ostream& out) {
		size_t row = car_.GetCoords().cell;
		out << std::setw(5) << row;
		PrintEdge(out);
		if (car_.GetCoords().line == car::Line::LEFT) {
			PrintCar(out);
		}
		else {
			PrintEmptyRoadSection(out);
		}
		PrintDivider(out, row);
		if (car_.GetCoords().line == car::Line::RIGHT) {
			PrintCar(out);
		}
		else {
			PrintEmptyRoadSection(out);
		}
		PrintEdge(out);
		out << std::endl;
	}

	void ConsoleDrawer::PrintCar(std::ostream& out) {
		switch (car_.GetCoords().direction_of_mov)
		{
		case car::DirectionOfMov::FORWARD:
			out << static_cast<char>(94);// ^
			break;
		case car::DirectionOfMov::BACKWARD:
			out << static_cast<char>(86);// V
			break;
		case car::DirectionOfMov::RIGHT:
			out << static_cast<char>(62);// >
			break;
		case car::DirectionOfMov::LEFT:
			out << static_cast<char>(60);// <
			break;
		}
	}

}