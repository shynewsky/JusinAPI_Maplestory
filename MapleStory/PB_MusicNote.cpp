#include "pch.h"
#include "PB_MusicNote.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CPB_MusicNote::CPB_MusicNote()
	: m_dwTime(GetTickCount())
{
}

CPB_MusicNote::~CPB_MusicNote()
{
	Release();
}

void CPB_MusicNote::Initialize()
{
#pragma region 히트박스크기 및 중점좌표 위치

	m_fRectCX = 75.f;
	m_fRectCY = 58.f;

	m_fBltCX = m_fRectCX;
	m_fBltCY = m_fRectCY;

	m_fFootHeight = 0.f;

	m_fBltX = m_fBltCX * 0.5;
	m_fBltY = m_fBltCY;

	m_tInfo.fY += m_fFootHeight;
	m_tInfo.fCX = m_fRectCX;
	m_tInfo.fCY = m_fRectCY;

#pragma endregion

	m_pFrameKey = L"boss_pinkbean_musicnote_effect_0,7";
	m_tFrame = { 0, 7, 0, 200, GetTickCount() };

	__super::Update_Rect();

}

int CPB_MusicNote::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPB_MusicNote::Late_Update()
{
	if (m_dwTime + 1400 < GetTickCount())
	{
		m_bDead = true;
		m_dwTime = GetTickCount();
	}

	__super::Move_Frame(); // 변경된 FRAME 값에 새로 애니메이션 구현

}

void CPB_MusicNote::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, 
	//	m_tInfo.fX + fScrollX - m_fBltX,
	//	m_tInfo.fY + fScrollY - m_fBltY,
	//	m_tInfo.fX + fScrollX - m_fBltX + m_fBltCX,
	//	m_tInfo.fY + fScrollY - m_fBltY + m_fBltCY
	//);

	GdiTransparentBlt(

		// TO
		hDC,											// 도착할 DC
		m_tInfo.fX + fScrollX - m_fBltX,
		m_tInfo.fY + fScrollY - m_fBltY,				// 좌상단에서부터
		m_fBltCX,
		m_fBltCY,										// 가로세로 이 길이만큼

		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * m_fBltCX,				// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * m_fBltCY,					// 몇행부터 세로 간격 얼만큼씩
		m_fBltCX,
		m_fBltCY,										// 한 이미지당 가로세로 이만큼씩 잘라서

		// Color
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CPB_MusicNote::Release()
{
}
