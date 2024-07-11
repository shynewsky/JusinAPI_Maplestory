#include "pch.h"
#include "MainUI_AssistBar.h"

#include "ObjMgr.h"
#include "BmpMgr.h"

#include "Player.h"

CMainUI_AssistBar::CMainUI_AssistBar()
{
}

CMainUI_AssistBar::~CMainUI_AssistBar()
{
	Release();
}

void CMainUI_AssistBar::Initialize()
{
	m_tInfo = { 248.f, 548.f, 155.f, 70.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_AssistHpBar1_0.bmp", L"BottomUI_AssistHpBar1_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_AssistHpBar2_0.bmp", L"BottomUI_AssistHpBar2_0");

	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_CurZero() == ZERO_ALPHA)
		m_pFrameKey = L"BottomUI_AssistHpBar2_0";
	else 
		m_pFrameKey = L"BottomUI_AssistHpBar1_0";
}

int CMainUI_AssistBar::Update()
{
	return 0;
}

void CMainUI_AssistBar::Late_Update()
{
	if (dynamic_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_CurZero() == ZERO_ALPHA)
		m_pFrameKey = L"BottomUI_AssistHpBar2_0";
	else
		m_pFrameKey = L"BottomUI_AssistHpBar1_0";
}

void CMainUI_AssistBar::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(
		// TO
		hDC,										// 도착할 DC
		m_tRect.left,
		m_tRect.top,								// 좌상단에서부터
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,							// 가로세로 이 길이만큼
		// FROM
		hMemDC,										// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,		// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,							// 한 이미지당 가로세로 이만큼씩 잘라서
		// COLOR
		RGB(255, 0, 255)							// 제거할 색상값	
	);
}

void CMainUI_AssistBar::Release()
{
}
