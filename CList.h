#pragma once
#include "framework.h"
#include "FleetBattle.h"

class CList
{
public:
	struct SSign;

	using PSSIGN = SSign*;
	using PCLIST = CList*;
	using PFSIGN = bool (*)(const PVOID, const PVOID);

private:
	struct SSign
	{
		PVOID  pfSign;
		PCLIST pList;
		PSSIGN pNext;

		SSign(PVOID pvoid, PCLIST clist = nullptr, PSSIGN pnext = nullptr) :
			pfSign(pvoid), pList(clist), pNext(pnext) {};
	};

	static PSSIGN pStart;

	PCLIST pNext;
	PVOID  pContent;
	PVOID  hInstance;

protected:
	CList(const PVOID, const PVOID, const PVOID);
	~CList();
	void GetIndex(PVOID);

public:
	CList() = delete;
};
