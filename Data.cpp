#include "Data.h"

using namespace domain;
UINT GetRandUINT(const UINT max) {
	return std::rand() / (RAND_MAX / max);
}

UINT Point::X() const {
	return x;
};
UINT Point::Y() const {
	return y;
};
bool Point::IsNan(const UINT max = -1) const {
	if (-1 == x || -1 == y)
		return true;
	if (x >= max || y >= max)
		return true;
	return false;
}
Point Point::Up() const {
	if (this->IsNan() || (y - 1 == -1))
		return Point{};
	else
		return Point{ x, y - 1 };
}
Point Point::Down() const {
	if (this->IsNan() || (y + 1 == -1))
		return Point{};
	else
		return Point{ x, y + 1 };
}
Point Point::Left() const {
	if (this->IsNan() || (x - 1 == -1))
		return Point{};
	else
		return Point{ x - 1, y };
}
Point Point::Right() const {
	if (this->IsNan() || (x - 1 == -1))
		return Point{};
	else
		return Point{ x + 1, y };
}

Point::Direct Point::RotateDirect(const Direct direct) {
	if (Direct::up == direct)
		return Direct::right;
	if (Direct::right == direct)
		return Direct::down;
	if (Direct::down == direct)
		return Direct::left;
	if (Direct::left == direct)
		return Direct::up;
}
Point::Direct Point::GetRandDirect() {
	return static_cast<Direct>(
		GetRandUINT(static_cast<UINT>(Direct::center)));
}

Point Point::MoveDirect(const Direct direct) const {
	if (Direct::up == direct)
		return this->Up();
	if (Direct::down == direct)
		return this->Down();
	if (Direct::left == direct)
		return this->Left();
	if (Direct::right == direct)
		return this->Right();
}