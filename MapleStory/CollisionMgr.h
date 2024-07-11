#pragma once

#include "Obj.h"
#include "Ui.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	// Obj 끼리 충돌
	static bool		CheckObj_Single(CObj* _Dst, CObj* _Src);
	static bool		CheckObj_Multi(list<CObj*> _Dst, list<CObj*> _Src);
	static CObj&	Collision_Obj(list<CObj*>& _Dst, list<CObj*>& _Src); // 원본전달(저장용)

	// UI 끼리 충돌
	static bool		MouseOver_Rect(list<CUi*> _Dst, list<CUi*> _Src);
	static int		SlotClick_Rect(list<CUi*> _Dst, vector<CUi*> _Src);
};