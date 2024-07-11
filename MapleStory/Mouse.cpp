#include "pch.h"
#include "Mouse.h"

#include "KeyMgr.h"
#include "BmpMgr.h"
#include "CollisionMgr.h"

#include "UiMgr.h"

#include "ObjMgr.h"

CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 38.f;
	m_tInfo.fCY = 38.f;
		
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Cursor/Cursor0_Normal_0.bmp", L"Cursor0_Normal_0");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Cursor/Cursor1_MouseOverClick_01.bmp", L"Cursor1_MouseOverClick_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Cursor/Cursor3_Click_0.bmp", L"Cursor3_Click_0");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Cursor/Cursor2_MouseOverGrab_012.bmp", L"Cursor2_MouseOverGrab_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Cursor/Cursor4_Grab_0.bmp", L"Cursor4_Grab_0");

	m_eCurState = M_NORMAL;
	m_pFrameKey = L"Cursor0_Normal_0";
	m_tFrame = { 0, 0, 0, 200, GetTickCount() };
}

int CMouse::Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

#pragma region 마우스 변화량 가져오기 (실패)

	//float fCurMouseX = (float)ptMouse.x;
	//float fCurMouseY = (float)ptMouse.y;

	//m_fDeltaX = fCurMouseX - m_tInfo.fX;
	//m_fDeltaY = fCurMouseY - m_tInfo.fY;

	//m_tInfo.fX = fCurMouseX;
	//m_tInfo.fY = fCurMouseY;

#pragma endregion

	Key_Input();

	__super::Update_Rect();

	//ShowCursor(false);
	ShowCursor(false);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update()
{
	Motion_Change();

	__super::Move_Frame();
}

void CMouse::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(

		// TO
		hDC,
		m_tRect.left - m_tInfo.fCX * 0.5,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		// FROM
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX, //--> 위치를 자르기 시작하는 좌상단
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,

		// COLOR
		RGB(255, 0, 255)
	);
}

void CMouse::Release()
{
}

void CMouse::Key_Input()
{
	bool bMenuButton =
		CCollisionMgr::MouseOver_Rect(
		CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_MOUSE),
		CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_MBUTTON));

	bool bInvenSlot =
		CCollisionMgr::MouseOver_Rect(
		CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_MOUSE),
		CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_ISLOT));

	if (bMenuButton == true)
	{
		m_eCurState = M_OVERC;
		m_pFrameKey = L"Cursor1_MouseOverClick_01";

		if (CKeyMgr::Get_Instance()->Key_ING(VK_LBUTTON))
		{
			m_eCurState = M_CLICK;
			m_pFrameKey = L"Cursor3_Click_0";
		}
	}

	else if (bInvenSlot == true)
	{
		m_eCurState = M_OVERG;
		m_pFrameKey = L"Cursor2_MouseOverGrab_012";

		if (CKeyMgr::Get_Instance()->Key_IN(VK_LBUTTON))
		{
			m_eCurState = M_CLICK;
			m_pFrameKey = L"Cursor4_Grab_0";
		}
	}

	else
	{
		m_eCurState = M_NORMAL;
		m_pFrameKey = L"Cursor0_Normal_0";

		if (CKeyMgr::Get_Instance()->Key_ING(VK_LBUTTON))
		{
			m_eCurState = M_CLICK;
			m_pFrameKey = L"Cursor3_Click_0";
		}
	}
}

void CMouse::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case M_NORMAL:
			m_tFrame = { 0,0,0,200, GetTickCount() };
			break;

		case M_CLICK:
			m_tFrame = { 0,0,0,200, GetTickCount() };
			break;

		case M_GRAB:
			m_tFrame = { 0,0,0,200, GetTickCount() };
			break;

		case M_OVERC:
			m_tFrame = { 0,1,0,200, GetTickCount() };
			break;

		case M_OVERG:
			m_tFrame = { 0,2,0,200, GetTickCount() };
			break;
		}

		m_ePreState = m_eCurState;
	}

}
