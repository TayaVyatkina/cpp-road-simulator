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

	size_t GetLength() const;

	DividerType GetDividerType(int) const;

private:
	std::deque<DividerType> road_;
};
}

