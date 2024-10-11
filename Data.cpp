#include "Data.h"

using namespace domain;

UINT Point::X() const {
	return x;
};
UINT Point::Y() const {
	return y;
};
bool Point::IsNan() const {
	return -1 == x || -1 == y;
}
bool Point::IsNan(const UINT max) const {
	return x > max || y > max;
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
	if (this->IsNan() || (x + 1 == -1))
		return Point{};
	else
		return Point{ x + 1, y };
}
HINSTANCE Data::GetHInstance() const {
	return hInstance;
};
Size Data::GetSize() const {
	return size;
};
Scale Data::GetScale() const {
	return scale;
};
Level Data::GetLevel() const {
	return level;
};
UINT Data::GetMaxUINT() const {
	return static_cast<UINT>(size) - 1;
}
UINT Data::GetSizeUINT() const {
	return static_cast<UINT>(size);
}
UINT Data::GetScaleUINT() const {
	return static_cast<UINT>(scale);
}
UINT Data::GetLevelUINT() const {
	return static_cast<UINT>(level);
}
Data::Data(const HINSTANCE hInstance_) :
	hInstance{ hInstance_ },
	size{ Size::size_10 },
	scale{ Scale::scale_2 },
	level{ Level::level_4 }
{
	std::srand(std::time(NULL));
};
