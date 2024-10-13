#include "Compare.h"

using namespace compare;

UINT Compare::LengthRaw(
	const CompFunc comp_func,
	const Point start,
	const Direct direct
) const {
	Point point = (&start->*direct)();
	if (false == point.IsNan(GetMaxUINT()))
		if ((this->*comp_func)(point))
			return LengthRaw(comp_func, point, direct) + 1;
	return 0;
}