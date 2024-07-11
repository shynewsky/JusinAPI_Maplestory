#include "pch.h"
#include "ItemSlotUI.h"

#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CItemSlotUI::CItemSlotUI()
{
}

CItemSlotUI::~CItemSlotUI()
{
	Release();
}

void CItemSlotUI::Initialize()
{
	m_tInfo.fCX = 42.f;
	m_tInfo.fCY = 42.f;

	__super::Update_Rect();
}

int CItemSlotUI::Update()
{
	return 0;
}

void CItemSlotUI::Late_Update()
{
}

void CItemSlotUI::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(

		// TO
		hDC,
		m_tInfo.fX + 5.f,
		m_tInfo.fY - 15.f,
		32.f,
		32.f,

		// FROM
		hMemDC,
		0,
		0,
		32.f,
		32.f,

		// COLOR
		RGB(255, 0, 255)
	);
}

void CItemSlotUI::Release()
{
}