#pragma once

#include "Ui.h"

template<typename T>
class CAbstractFactoryUI
{
public:
	static CUi* Create()
	{
		CUi* pUi = new T;

		pUi->Initialize();
		return pUi;
	}

	static CUi* Create(float _fX, float _fY)
	{
		CUi* pUi = new T;
		pUi->Set_Pos(_fX, _fY);

		pUi->Initialize();
		return pUi;
	}

	static CUi* Create(float _fX, float _fY, TCHAR* pFrameKey)
	{
		CUi* pUi = new T;
		pUi->Set_Pos(_fX, _fY);
		pUi->Set_FrameKey(pFrameKey);

		pUi->Initialize();
		return pUi;
	}

public:
	CAbstractFactoryUI() {}
	~CAbstractFactoryUI() {}
};