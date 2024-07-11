#pragma once

#include "Define.h"

class CUi
{
public:
	CUi();
	virtual ~CUi();

public:
	virtual void	Initialize() {}/*PURE;*/
	virtual int		Update() { return 0; }/*PURE;*/
	virtual void	Late_Update() {}/*PURE;*/
	virtual void	Render(HDC hDC) {}/*PURE;*/
	virtual void	Release() {}/*PURE;*/

	//--------------------------------------------------------------------//

protected:
	INFO	m_tInfo; // 중점좌표, 한변의길이
	RECT	m_tRect; // 각변의 좌표, 콜라이더(히트박스)
	float	m_fSpeed;

protected:
	float	m_fRectCX;	// 히트박스 가로세로
	float	m_fRectCY;

	float	m_fBltCX;	// 애니메이션 가로세로
	float	m_fBltCY;

	float	m_fBltX;	// 애니메이션 좌상단 시작점
	float	m_fBltY;

	float	m_fFootHeight; // 애니메이션에서 발바닥 공중부양 위치

protected:
	void	Update_Rect();

public:
	INFO	Get_Info() { return m_tInfo; }
	RECT	Get_Rect() { return m_tRect; }
	void	Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }

	//--------------------------------------------------------------------//

protected:
	FRAME			m_tFrame;			// 어디부터 어디까지 어떤 속도로 넘어가는지를 담은 구조체 자료형
	const TCHAR*	m_pFrameKey = L"";	// 어떤 이미지를 꺼내와야 할지 넣는 키 값
	bool			m_bTemp;

protected:
	void	Move_Frame();		// FRAME 구조체에 담긴 값으로 애니메이션화 하는 함수

public:
	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	const TCHAR*	Get_FrameKey() { return m_pFrameKey; }

	//--------------------------------------------------------------------//

public:
	void	Remove_PopUpUI();
	void	Remove_InventoryUI();

	//--------------------------------------------------------------------//

protected:
	vector<CUi*>	m_vecSlot;

public:
	vector<CUi*>	Get_Slot() { return m_vecSlot; }
	CUi*			Get_EmptySlot()
	{
		for (auto& Slot : m_vecSlot)
		{
			if (Slot->Get_FrameKey() == L"")
			{
				return Slot;
			}
		}
		return nullptr;
	}

protected:
	ITEMNAME		m_eItemName;
	ITEMTYPE		m_eItemType;

public:
	ITEMNAME		Get_ItemName() { return m_eItemName; }
	ITEMTYPE		Get_ItemType() { return m_eItemType; }

	void			Set_ItemName(ITEMNAME _eItemName) { m_eItemName = _eItemName; }
	void			Set_ItemType(ITEMTYPE _eItemType) { m_eItemType = _eItemType; }

	//--------------------------------------------------------------------//

};