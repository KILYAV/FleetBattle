#include "CList.h"

CList::PSSIGN CList::pStart = nullptr;

CList::CList(PVOID pfsign, PVOID pcontent, PVOID hinstance) :
	pNext(nullptr),
	pContent(pcontent),
	hInstance(hinstance)
{
	if (NULL == pStart)
		pStart = new SSign(pfsign);

	PSSIGN psSign = pStart;
	while (psSign->pfSign != pfsign)
	{
		if (psSign->pNext)
			psSign = psSign->pNext;
		else
			psSign = psSign->pNext = new SSign(pfsign);
	}

	if (psSign->pList)
	{
		PCLIST pcList = psSign->pList;
		while (pcList->pNext)
			pcList = pcList->pNext;
		pcList->pNext = this;
	}
	else
		psSign->pList = this;
}
CList::~CList()
{
	PSSIGN pSign = pStart;
	PCLIST pList = pStart->pList;

	PSSIGN pPreySign = nullptr;
	PCLIST pPreyList = nullptr;

	while (this != pList)
	{
		if (pList->pNext)
			pList = (pPreyList = pList)->pNext;
		else
			pList = (pSign = (pPreySign = pSign)->pNext)->pList;
	}

	if (this != pSign->pList)
		pPreyList->pNext = pList->pNext;
	else
		if (pList->pNext)
			pSign->pList = pList->pNext;
		else
			if (pPreySign)
				pPreySign->pNext = pSign->pNext;
			else
				pStart = pSign->pNext;
}

void CList::GetIndex(PVOID pVoid)
{
	;
}
