#include "pch.h"
#include "MainUI_ExpBar.h"

#include "BmpMgr.h"

CMainUI_ExpBar::CMainUI_ExpBar()
{
}

CMainUI_ExpBar::~CMainUI_ExpBar()
{
	Release();
}

void CMainUI_ExpBar::Initialize()
{
	m_tInfo = { 0.f, 595.f, 800.f, 10.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_ExpBar_0.bmp", L"BottomUI_ExpBar_0");
	m_pFrameKey = L"BottomUI_ExpBar_0";
}

int CMainUI_ExpBar::Update()
{
	return 0;
}

void CMainUI_ExpBar::Late_Update()
{
}

void CMainUI_ExpBar::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(
		// TO
		hDC,											// 도착할 DC
		m_tRect.left, m_tRect.top,						// 좌상단에서부터
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,				// 가로세로 이 길이만큼
		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,				// 한 이미지당 가로세로 이만큼씩 잘라서
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CMainUI_ExpBar::Release()
{
}
