#include "pch.h"
#include "BossUI_Bt1_Normal.h"

#include "KeyMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"

CBossUI_Bt1_Normal::CBossUI_Bt1_Normal()
{
}

CBossUI_Bt1_Normal::~CBossUI_Bt1_Normal()
{
	Release();
}

void CBossUI_Bt1_Normal::Initialize()
{
	m_tInfo.fCX = 154.f;
	m_tInfo.fCY = 42.f;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BossUI/BossUI_EnterButton_normal_0123.bmp", L"BossUI_EnterButton_normal_0123");
	m_pFrameKey = L"BossUI_EnterButton_normal_0123";
}

int CBossUI_Bt1_Normal::Update()
{
	__super::Update_Rect();

	return 0;
}

void CBossUI_Bt1_Normal::Late_Update()
{
	POINT	ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&m_tRect, ptMouse))
	{
		m_iDrawID = 1; // mouse_over
	}
	else
		m_iDrawID = 0; // normal
}

void CBossUI_Bt1_Normal::Render(HDC hDC)
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

void CBossUI_Bt1_Normal::Release()
{
}
