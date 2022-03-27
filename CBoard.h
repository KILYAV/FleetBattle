#pragma once
#include "framework.h"
#include "Resource.h"
#include "CBase.h"

class CBoard : virtual protected CBase
{
public:
	enum ELevel
	{
		eLevel0,
		eLevel1,
		eLevel2,
		eLevel3,
		eLevel4,
		eLevel5
	};

private:
	UINT   mSelect;
	UINT   mMaxLevel;
	PUINT  aFleet[eBoardTotal];
	PUINT  pFleet;
	P2UINT aBoard[eBoardTotal];
	P2UINT aCover[eBoardTotal];
	P2UINT pBoard;

private:
	bool AddCellHorizon(const SPoint&, const UINT);
	bool AddCellVertical(const SPoint&, const UINT);
	bool CreateShipHorizon(const SPoint&, const UINT);
	bool CreateShipVertical(const SPoint&, const UINT);

	UINT TestTripletHorizon(const UINT, const UINT);
	UINT TestTripletVertical(const UINT, const UINT);

	UINT TestLineUp(const UINT, const UINT);
	UINT TestLineDown(const UINT, const UINT);
	UINT TestLineLeft(const UINT, const UINT);
	UINT TestLineRight(const UINT, const UINT);

	UINT TestDiagonal(const SPoint&, const UINT);

private:
	bool (CBoard::* CreateShipRandom)(const SPoint&, const UINT);

protected:
	CBoard();
	~CBoard();

protected:
	UINT CreateShip(const SPoint&, const UINT);
	UINT DeleteShip(const SPoint&, const UINT);

	void RandomOrder();
	bool TestLevelShip();

	P3UINT const GetBoard() { return aBoard; };
	void Select(bool);

	bool HitCover(const SPoint&, const UINT);
	void HitDiagonal(const SPoint&, const UINT);
};
