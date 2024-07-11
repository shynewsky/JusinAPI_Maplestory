#include "pch.h"
#include "YellowFox.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"

#include "ObjMgr.h"

#include "CollisionMgr.h"

CYellowFox::CYellowFox()
	: m_dwTime(GetTickCount())
{
}

CYellowFox::~CYellowFox()
{
	Release();
}

void CYellowFox::Initialize()
{
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Pet/Pet_YelloFox_left_0,7.bmp", L"Pet_YelloFox_left_0,7");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Pet/Pet_YelloFox_right_0,7.bmp", L"Pet_YelloFox_right_0,7");

	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 33.f;
	m_fSpeed = 100.f;

	m_pFrameKey = L"Pet_YelloFox_left_0,7";
	m_tFrame = { 0, 7, 0, 200, GetTickCount() };

	__super::Update_Rect();
}

int CYellowFox::Update()
{
	if (m_bDead)
		return OBJ_DEAD; // 주워가면 죽은걸로

	Move_Around();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CYellowFox::Late_Update()
{
	float	fY(0.f);
	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	if (bLineCol)
	{
		m_tInfo.fY = fY;
	}

	__super::Move_Frame();
}

void CYellowFox::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
	//	m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	GdiTransparentBlt(
		// TO
		hDC,											// 도착할 DC
		m_tRect.left + fScrollX,
		m_tRect.top + fScrollY,							// 좌상단에서부터
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,								// 가로세로 이 길이만큼

		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,								// 한 이미지당 가로세로 이만큼씩 잘라서

		// COLOR
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CYellowFox::Release()
{
}

void CYellowFox::Move_Around()
{
	float fGoalX = CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX;
	DIRID eDir = CObjMgr::Get_Instance()->Get_Player()->Get_Dir();

	if (eDir == DIR_LEFT) // 왼쪽을 향할때
	{
		m_pFrameKey = L"Pet_YelloFox_left_0,7";

		m_tInfo.fX = fGoalX + m_fSpeed;
	}
	else if (eDir == DIR_RIGHT) // 오른쪽을 향할때
	{
		m_pFrameKey = L"Pet_YelloFox_right_0,7";

		m_tInfo.fX = fGoalX - m_fSpeed;
	}
}
