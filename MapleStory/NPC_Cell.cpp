#include "pch.h"
#include "NPC_Cell.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

CNPC_Cell::CNPC_Cell()
{
}

CNPC_Cell::~CNPC_Cell()
{
}

void CNPC_Cell::Initialize()
{

#pragma region 히트박스크기 및 중점좌표 위치

	m_fRectCX = 70.f;
	m_fRectCY = 72.f;

	m_fBltCX = 70.f;
	m_fBltCY = 72.f;

	m_fBltX = m_fBltCX * 0.5;
	m_fBltY = m_fBltCY - m_fFootHeight;

	m_tInfo = { 1025.f, 205.f, m_fRectCX, m_fRectCY };

#pragma endregion

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/NPC/NPC_cell_0,8.bmp", L"NPC_cell_0,8");
	m_tFrame = { 0, 8, 0, 300, GetTickCount() };
	m_pFrameKey = L"NPC_cell_0,8";
	
}

int CNPC_Cell::Update()
{
	return 0;
}

void CNPC_Cell::Late_Update()
{
	__super::Move_Frame();
}

void CNPC_Cell::Render(HDC hDC)
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

void CNPC_Cell::Release()
{
}
