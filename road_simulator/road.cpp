#include "road.h"

namespace road {

Road::Road()
	:road_()
{}

void Road::AddSection(size_t len, DividerType divider) {
	for (size_t i = 0; i < len; ++i) {
		road_.emplace_back(divider);
	}
}

size_t Road::GetLength() const {
	return road_.size();
}

DividerType Road::GetDividerType(int road_section) const {
	return road_.at(road_section);
}

}// namespace road 