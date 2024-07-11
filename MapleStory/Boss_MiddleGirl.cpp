#include "pch.h"
#include "Boss_MiddleGirl.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

CBoss_MiddleGirl::CBoss_MiddleGirl()
	: m_fNpcWidth(370.f), m_fNpcHeight(370.f), m_fNpcFootX(905.f), m_fNpcFootY(300.f)
{
}

CBoss_MiddleGirl::~CBoss_MiddleGirl()
{
}

void CBoss_MiddleGirl::Initialize()
{
	m_tInfo = { m_fNpcFootX, m_fNpcFootY - m_fNpcHeight * 0.5f,
		m_fNpcWidth, m_fNpcHeight };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_MiddleiGirl_stone_0.bmp", L"boss_MiddleiGirl_stone_0");
	m_tFrame = { 0, 0, 0, 300, GetTickCount() };
	m_pFrameKey = L"boss_MiddleiGirl_stone_0";
}

int CBoss_MiddleGirl::Update()
{
	return 0;
}

void CBoss_MiddleGirl::Late_Update()
{
	__super::Move_Frame();

}

void CBoss_MiddleGirl::Render(HDC hDC)
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

void CBoss_MiddleGirl::Release()
{
}
