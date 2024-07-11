#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, DIRID eDir) // ½ºÅ³¹æÇâ
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_Dir(eDir);
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float _fX, float _fY, TCHAR* pFrameKey) // Æê
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Set_FrameKey(pFrameKey);

		pObj->Initialize();
		return pObj;
	}

public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};