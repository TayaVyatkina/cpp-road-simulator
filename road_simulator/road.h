#pragma once
#include <deque>
namespace road {
enum class DividerType {
	SOLID,
	DOTTED
};

class Road {
public:
	explicit Road();

	void AddSection(size_t, DividerType);

	size_t GetLength();

	DividerType GetDividerType(int);

private:
	std::deque<DividerType> road_;
};
}

