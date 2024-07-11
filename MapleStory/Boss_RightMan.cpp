#include "pch.h"
#include "Boss_RightMan.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

CBoss_RightMan::CBoss_RightMan()
	: m_fNpcWidth(460.f), m_fNpcHeight(880.f), m_fNpcFootX(1561.f), m_fNpcFootY(625.f)
{
}

CBoss_RightMan::~CBoss_RightMan()
{
}

void CBoss_RightMan::Initialize()
{
	m_tInfo = { m_fNpcFootX, m_fNpcFootY - m_fNpcHeight * 0.5f,
		m_fNpcWidth, m_fNpcHeight };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_RIghtMan_stone_0.bmp", L"boss_RIghtMan_stone_0");
	m_tFrame = { 0, 0, 0, 300, GetTickCount() };
	m_pFrameKey = L"boss_RIghtMan_stone_0";
}

int CBoss_RightMan::Update()
{
	return 0;
}

void CBoss_RightMan::Late_Update()
{
	__super::Move_Frame();

}

void CBoss_RightMan::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
	//	m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	GdiTransparentBlt(
		// TO
		hDC,												// 도착할 DC
		m_tRect.left + fScrollX, m_tRect.top + fScrollY,	// 좌상단에서부터
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,					// 가로세로 이 길이만큼
		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,				// 한 이미지당 가로세로 이만큼씩 잘라서
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CBoss_RightMan::Release()
{
}
