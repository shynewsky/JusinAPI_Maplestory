#include "pch.h"
#include "Item_WhitePotion.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

CItem_WhitePotion::CItem_WhitePotion()
{
}

CItem_WhitePotion::~CItem_WhitePotion()
{
	Release();
}

void CItem_WhitePotion::Initialize()
{
	m_eItemName = INAME_WhitePotion;
	m_eItemType = ITYPE_CONSUME;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Item/Item_WhitePotion_drop.bmp", L"Item_WhitePotion_drop");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Item/Item_WhitePotion_slot.bmp", L"Item_WhitePotion_slot");

	m_pFrameKey = L"Item_WhitePotion_drop";
}

int CItem_WhitePotion::Update()
{
	if (m_bDead)
		return OBJ_DEAD; // 주워가면 죽은걸로

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem_WhitePotion::Late_Update()
{
	float	fY(0.f);
	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CItem_WhitePotion::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
	//	m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	GdiTransparentBlt(
		// TO
		hDC,											// 도착할 DC
		m_tRect.left + fScrollX,
		m_tRect.top + fScrollY,							// 좌상단에서부터
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,								// 가로세로 이 길이만큼

		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,								// 한 이미지당 가로세로 이만큼씩 잘라서

		// COLOR
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CItem_WhitePotion::Release()
{
}
