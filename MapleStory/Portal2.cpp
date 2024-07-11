#include "pch.h"
#include "Portal2.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

CPortal2::CPortal2()
{
}

CPortal2::~CPortal2()
{
}

void CPortal2::Initialize()
{
	m_tInfo.fCX = 90.f;
	m_tInfo.fCY = 120.f;

	__super::Update_Rect();

	//CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Portal_0,7.bmp", L"Portal_0,7");
	//m_tFrame = { 0, 7, 0, 100, GetTickCount() };
	//m_pFrameKey = L"Portal_0,7";
}

int CPortal2::Update()
{
	return 0;
}

void CPortal2::Late_Update()
{
	__super::Move_Frame();
}

void CPortal2::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	//HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
	//	m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	//GdiTransparentBlt(
	//	// TO
	//	hDC,												// 도착할 DC
	//	m_tRect.left + fScrollX, m_tRect.top + fScrollY,	// 좌상단에서부터
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,					// 가로세로 이 길이만큼
	//	// FROM
	//	hMemDC,											// 출발할 DC
	//	m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
	//	m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,				// 한 이미지당 가로세로 이만큼씩 잘라서
	//	RGB(255, 0, 255)								// 제거할 색상값	
	//);
}

void CPortal2::Release()
{
}
