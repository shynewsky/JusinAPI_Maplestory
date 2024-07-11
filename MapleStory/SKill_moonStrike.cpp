#include "pch.h"
#include "SKill_moonStrike.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CSKill_moonStrike::CSKill_moonStrike()
	: m_dwTime(GetTickCount())
{
}

CSKill_moonStrike::~CSKill_moonStrike()
{
	Release();
}

void CSKill_moonStrike::Initialize()
{
#pragma region 히트박스크기 및 중점좌표 위치

	m_fRectCX = 475.f;
	m_fRectCY = 83.f;

	m_fBltCX = m_fRectCX;
	m_fBltCY = m_fRectCY;

	m_fFootHeight = 0.f;

	m_fBltX = m_fBltCX * 0.5;
	m_fBltY = m_fBltCY;

	m_tInfo.fY += m_fFootHeight;
	m_tInfo.fCX = m_fRectCX;
	m_tInfo.fCY = m_fRectCY;

#pragma endregion

	if (m_eDir == DIR_LEFT)
	{
		m_pFrameKey = L"alpha_skill0_moonStrike_effect_left_01234";
	}

	else if (m_eDir == DIR_RIGHT)
	{
		m_pFrameKey = L"alpha_skill0_moonStrike_effect_right_01234";
	}

	m_tFrame = { 0, 4, 0, 100, GetTickCount() };

	CSoundMgr::Get_Instance()->PlaySound(L"Alpha_MoonStrike_Use_101001200.mp3", SOUND_EFFECT, 1.f);

	__super::Update_Rect();
}

int CSKill_moonStrike::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CSKill_moonStrike::Late_Update()
{
	if (m_dwTime + 500 < GetTickCount())
	{
		m_bDead = true;
		m_dwTime = GetTickCount();
	}

	__super::Move_Frame(); // 변경된 FRAME 값에 새로 애니메이션 구현
}

void CSKill_moonStrike::Render(HDC hDC)
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

void CSKill_moonStrike::Release()
{
}
