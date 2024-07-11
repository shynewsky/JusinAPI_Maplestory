#include "pch.h"
#include "CollisionMgr.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::CheckObj_Single(CObj* _Dst, CObj* _Src)
{
	RECT	rcRect{};

	if (IntersectRect(&rcRect, &(_Dst->Get_Rect()), &(_Src->Get_Rect())))
		return true;

	else
		return false;
}

bool CCollisionMgr::CheckObj_Multi(list<CObj*> _Dst, list<CObj*> _Src)
{
	RECT	rcRect{};
	bool	bIntersect = false;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			// & 앞에 L-value가 필요합니다 --> CObj::RECT Get_Rect()를 RECT& Get_Rect()로 바꾸니까 된다 

			if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				bIntersect = true;
			}
			else
			{
				if (bIntersect == false)
					bIntersect = false;
			}
		}
	}
	return bIntersect;
}

CObj& CCollisionMgr::Collision_Obj(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT	rcRect{};
	CObj*	pItem = nullptr;
	bool	bIntersect = false;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				pItem = Src;
				bIntersect = true;
			}
			else
			{
				if (bIntersect == false)
					bIntersect = false;
			}
		}
	}
	return *pItem;
}

bool CCollisionMgr::MouseOver_Rect(list<CUi*> _Dst, list<CUi*> _Src)
{
	RECT	rcRect{};

	bool	bIntersect = false;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				bIntersect = true;
			}
			else
			{
				if (bIntersect == false)
					bIntersect = false;
			}
		}
	}
	return bIntersect;
}

int CCollisionMgr::SlotClick_Rect(list<CUi*> _Dst, vector<CUi*> _Src)
{
	RECT	rcRect{};

	int		iCount(0);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rcRect, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				return iCount;

			}
			++iCount;
		}
	}
}

