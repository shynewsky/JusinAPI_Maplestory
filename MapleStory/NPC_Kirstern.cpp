#include "pch.h"
#include "NPC_Kirstern.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

#include "UiMgr.h"
#include "AbstractFactoryUI.h"

#include "BossUI_CallBox.h"

#include "SceneMgr.h"


CNPC_Kirstern::CNPC_Kirstern()
{
}

CNPC_Kirstern::~CNPC_Kirstern()
{
}

void CNPC_Kirstern::Initialize()
{
#pragma region 히트박스크기 및 중점좌표 위치

	m_fRectCX = 80.f + 300.f;
	m_fRectCY = 87.f;

	m_fBltCX = 80.f;
	m_fBltCY = 87.f;

	m_fBltX = m_fBltCX * 0.5;
	m_fBltY = m_fBltCY;

	m_tInfo = { 650.f, 672.f, m_fRectCX, m_fRectCY };

#pragma endregion

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/NPC/NPC_Kistern1_0,8.bmp", L"NPC_Kistern1_0,8");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/NPC/NPC_Kirstern1_0,12.bmp", L"NPC_Kirstern1_0,12");
	m_tFrame = { 0, 8, 0, 300, GetTickCount() };
	m_pFrameKey = L"NPC_Kistern1_0,8";
}

int CNPC_Kirstern::Update()
{
	return 0;
}

void CNPC_Kirstern::Late_Update()
{
#pragma region 	NPC 주변에서 SPACE 누르면 대화창

	bool bCollide = CCollisionMgr::CheckObj_Single(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER).front()
		, CObjMgr::Get_Instance()->Get_TypeObj(OBJ_NPC).back());

	if (bCollide == true &&
		CKeyMgr::Get_Instance()->Key_IN(VK_SPACE) &&
		CSceneMgr::Get_Instance()->Get_PBVideo() == false)
	{
		CUiMgr::Get_Instance()->Add_Object(UI_POPUP, CAbstractFactoryUI<CBossUI_CallBox>::Create());
		return;
	}

#pragma endregion


	__super::Move_Frame();
}

void CNPC_Kirstern::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
	//	m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

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

void CNPC_Kirstern::Release()
{
}
