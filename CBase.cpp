#include <time.h>
#include "CBase.h"

UINT CBase::RandomUINT(const UINT max)
{
	time_t mTime;
	time(&mTime);
	UINT random = static_cast<UINT>(mTime) + rand();
	return random - random / max * max;
}