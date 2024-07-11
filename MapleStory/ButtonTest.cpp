#include "pch.h"
#include "ButtonTest.h"

#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CButtonTest::CButtonTest()
{
}

CButtonTest::~CButtonTest()
{
	Release();
}

void CButtonTest::Initialize()
{
	m_tInfo = { 608.f, 567.5f, 34.f, 37.f };

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu0_cash_0123.bmp", L"BottomUI_menu0_cash_0123");
	m_pFrameKey = L"BottomUI_menu0_cash_0123";
}

int CButtonTest::Update()
{
	__super::Update_Rect();

	return 0;
}

void CButtonTest::Late_Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_IN(VK_LBUTTON))
		{
			if(!lstrcmp(L"BottomUI_menu0_cash_0123", m_pFrameKey))
				m_iDrawID = 2; // pressed

			return;
		}
		m_iDrawID = 1; // mouse_over
	}
	else
		m_iDrawID = 0; // normal
}

void CButtonTest::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(
		
		// TO
		hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		// FROM
		hMemDC,
		m_iDrawID * (int)m_tInfo.fCX, //--> 위치를 자르기 시작하는 좌상단
		0,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		RGB(255, 0, 255)
	);

}

void CButtonTest::Release()
{
}
