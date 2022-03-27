#pragma once
#include "framework.h"
#include "Resource.h" 

class CBase
{
public:
	enum
	{
		//----------
		eSea = 0,
		eSky,
		eShip,
		eBlast,
		eMissle,
		eCellTotal,

		//----------
		eAllies = 0,
		eEnemy,
		eBoardTotal,

		eMain = eBoardTotal,
		eFrameTotal,

		//----------
		eCenter = 0,
		eUp,
		eDown,
		eLeft,
		eRight,
		eDirectTotal,

		//-----------
		eSize10 = 10,
		eSize20 = 20,
		eSize40 = 40
	};

	struct SPoint
	{
		UINT x;
		UINT y;
		SPoint(const UINT X = 0, const UINT Y = 0) : x(X), y(Y) {};
	};

public:
	using PSPOINT = SPoint*;
	using P2UINT = PUINT*;
	using P3UINT = P2UINT*;
	using PHDC = HDC*;

private:
	UINT mSizeBoard;

protected:
	CBase() : mSizeBoard(eSize10) {};

protected:
	UINT RandomUINT(const UINT max);
	void RandomPoint(SPoint& point)
	{
		point = { RandomUINT(point.x), RandomUINT(point.y) };
	}
	SPoint RandomPoint(const UINT max)
	{
		return { RandomUINT(max), RandomUINT(max) };
	}

	UINT const GetSizeBoard() { return mSizeBoard; };

	virtual P3UINT const GetBoard() = 0;
};