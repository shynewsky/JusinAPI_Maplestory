#include "pch.h"
#include "MainUI_Bt3_Commu.h"

#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CMainUI_Bt3_Commu::CMainUI_Bt3_Commu()
{
}

CMainUI_Bt3_Commu::~CMainUI_Bt3_Commu()
{
	Release();
}

void CMainUI_Bt3_Commu::Initialize()
{
	m_tInfo = { 688.f, 567.5f, 32.f, 33.f };

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu3_commu_0123.bmp", L"BottomUI_menu3_commu_0123");
	m_pFrameKey = L"BottomUI_menu3_commu_0123";
}

int CMainUI_Bt3_Commu::Update()
{
	__super::Update_Rect();

	return 0;
}

void CMainUI_Bt3_Commu::Late_Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		if (CKeyMgr::Get_Instance()->Key_IN(VK_LBUTTON))
		{
			if (!lstrcmp(L"BottomUI_menu3_commu_0123", m_pFrameKey))
				m_iDrawID = 2; // pressed

			return;
		}
		m_iDrawID = 1; // mouse_over
	}
	else
		m_iDrawID = 0; // normal
}

void CMainUI_Bt3_Commu::Render(HDC hDC)
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

void CMainUI_Bt3_Commu::Release()
{
}
