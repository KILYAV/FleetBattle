#pragma
#include "framework.h"
#include "FleetBattle.h"

class CPoint
{
private:
	UINT X;
	UINT Y;

public:
	CPoint(UINT x, UINT y) { X = x, Y = y; };

	void operator +(CPoint& point) { X += point.X, Y += point.Y; };
	void operator -(CPoint& point) { X -= point.X, Y -= point.Y; };

	friend CPoint operator +(CPoint& A, CPoint& B) { return { A.X + B.X, A.Y + B.Y }; };
	friend CPoint operator -(CPoint& A, CPoint& B) { return { A.X - B.X, A.Y - B.Y }; };
};
