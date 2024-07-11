#pragma once

#include "Ui.h"

class CMouse : public CUi
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	//-----------------------------------------------------

private:
	enum MOUSEID { M_NORMAL, M_CLICK, M_GRAB, M_OVERC, M_OVERG, M_END };

	MOUSEID		m_ePreState;
	MOUSEID		m_eCurState;

	void	Key_Input();
	void	Motion_Change();

	//-----------------------------------------------------

	// 마우스 움직임 변화량 가져오기

//private:
//	float	m_fDeltaX;
//	float	m_fDeltaY;
//
//public:
//	float	Get_DeltaX() { return m_fDeltaX; }
//	float	Get_DeltaY() { return m_fDeltaY; }
};

