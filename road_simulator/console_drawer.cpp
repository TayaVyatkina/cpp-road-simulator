#include <algorithm>
#include <iomanip>

#include "console_drawer.h"

namespace drawer {

	ConsoleDrawer::ConsoleDrawer(car::Car& car, road::Road& road)
		: car_(car)
		, road_(road)
	{}

	void ConsoleDrawer::DrawRoad(std::ostream& out) {
		system("cls");// clear console

		// default len_of_view_section = 10;
		int len_of_view_section = std::min(static_cast<int>(car_.GetCoords().cell) + 9, static_cast<int>(road_.GetLength()) - 1);

		if (len_of_view_section >= 0) {
			if (road_.GetLength() == 1) {
				PrintFence(out);
				PrintSectionWithCar(out);
				PrintFence(out);
			}
			else {
				for (int row = len_of_view_section; row >= 0; --row) {
					// машина в последнем участке дороги или в тупике
					if (row == road_.GetLength() - 1) {
						PrintFence(out);
						if (car_.GetCoords().cell == road_.GetLength()) {
							PrintSectionWithCar(out);
							continue;
						}
					}

					if (row == car_.GetCoords().cell) {
						PrintSectionWithCar(out);
					}

					// машина в первом участке дороги или в тупике
					if (row == 0) {
						if (car_.GetCoords().cell == -1) {
							PrintSectionWithCar(out);
						}
						if (row < car_.GetCoords().cell) {
							PrintEmptyRoadSection(out, row);
						}
						PrintFence(out);
						continue;
					}

					if (row != car_.GetCoords().cell) {
						PrintEmptyRoadSection(out, row);
					}
				}
			}
		}
	}


	void ConsoleDrawer::PrintEmptyRoadSection(std::ostream& out, size_t row) {
		out << std::setw(5) << row;// section (cell) number
		PrintEdge(out);
		PrintEmpty(out);
		PrintDivider(out, row);
		PrintEmpty(out);
		PrintEdge(out);
		out << '\n';
	}

	void ConsoleDrawer::PrintSectionWithCar(std::ostream& out) {
		// if coords > road length or < 0, then print car on the first/last road section
		size_t row = car_.GetCoords().cell == -1 ? 0 : (car_.GetCoords().cell == road_.GetLength() ? road_.GetLength() - 1 : car_.GetCoords().cell);
		out << std::setw(5) << row;
		PrintEdge(out);

		// left side
		if (car_.GetCoords().line == car::Line::LEFT) {
			PrintCar(out);
		}
		else {
			PrintEmpty(out);
		}
		PrintDivider(out, row);

		// right side
		if (car_.GetCoords().line == car::Line::RIGHT) {
			PrintCar(out);
		}
		else {
			PrintEmpty(out);
		}
		PrintEdge(out);
		out << '\n';
	}

	void ConsoleDrawer::PrintEdge(std::ostream& out) {
		out << static_cast<char>(124);
	}

	void ConsoleDrawer::PrintEmpty(std::ostream& out) {
		out << " ";
	}

	void ConsoleDrawer::PrintDivider(std::ostream& out, size_t row) {
		out << (road_.GetDividerType(row) == road::DividerType::DOTTED ? static_cast<char>(58) : static_cast<char>(124));
	}

	void ConsoleDrawer::PrintFence(std::ostream& out) {
		out << "     |###|\n";
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

}// namespace drawer 