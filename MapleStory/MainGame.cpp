#include "pch.h"
#include "MainGame.h"

#include "AbstractFactory.h"

#include "ObjMgr.h"
#include "LineMgr.h"
#include "UIMgr.h"

#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "Player.h"

#include "AbstractFactoryUI.h"
#include "MainUI_ExpBar.h"
#include "MainUI_ExpGauge.h"
#include "MainUI_HpTpBar1.h"
#include "MainUI_HpTpGauge1.h"
#include "MainUI_HpTpGauge2.h"
#include "MainUI_HpTpBar2.h"

#include "MainUI_AssistBar.h"
#include "MainUI_AssistHp.h"
#include "MainUI_AssistTp.h"

#include "MainUI_Bt0_Cash.h"
#include "MainUI_Bt1_Event.h"
#include "MainUI_Bt2_Char.h"
#include "MainUI_Bt3_Commu.h"
#include "MainUI_Bt4_Setting.h"
#include "MainUI_Bt5_Option.h"

#include "Mouse.h"

CMainGame::CMainGame() : m_iFPS(0), m_dwTime(GetTickCount())
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

#pragma region 개발자모드 (시연회할때 삭제해야함)

//#ifdef _DEBUG
//
//	if (::AllocConsole() == TRUE)
//	{
//		FILE* nfp[3];
//		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//		std::ios::sync_with_stdio();
//	}
//
//#endif // _DEBUG

#pragma endregion

#pragma region 배경

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/back_black_1920,1080.bmp", L"back_black_1920,1080");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/back_black_1920,1080.bmp", L"back_black_1920,1080_2");

	CSoundMgr::Get_Instance()->Initialize();

	CUiMgr::Get_Instance()->Add_Object(UI_MOUSE, CAbstractFactoryUI<CMouse>::Create());

#pragma endregion

#pragma region 플레이어

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create());

#pragma endregion

#pragma region 게이지UI

	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_ExpBar>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUi_ExpGauge>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_HpTpBar1>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_HpTpGauge1>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_HpTpGauge2>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_HpTpBar2>::Create());

	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_AssistBar>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_AssistHp>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MAIN, CAbstractFactoryUI<CMainUI_AssistTp>::Create());

#pragma endregion

#pragma region 버튼UI

	CUiMgr::Get_Instance()->Add_Object(UI_MBUTTON, CAbstractFactoryUI<CMainUI_Bt0_Cash>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MBUTTON, CAbstractFactoryUI<CMainUI_Bt1_Event>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MBUTTON, CAbstractFactoryUI<CMainUI_Bt2_Char>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MBUTTON, CAbstractFactoryUI<CMainUI_Bt3_Commu>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MBUTTON, CAbstractFactoryUI<CMainUI_Bt4_Setting>::Create());
	CUiMgr::Get_Instance()->Add_Object(UI_MBUTTON, CAbstractFactoryUI<CMainUI_Bt5_Option>::Create());

#pragma endregion

	CSceneMgr::Get_Instance()->Scene_Change(Scene0_ZeroTemple); // 순서 바꾸면 안됨, Initialize 마지막에 호출해야함

	CKeyMgr::Get_Instance();
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
	CUiMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
	CUiMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
#pragma region fps(frame per second) 출력

	++m_iFPS;

	if (m_dwTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}

#pragma endregion

#pragma region 더블 버퍼링

	if (Scene8_PinkbeanVideo == CSceneMgr::Get_Instance()->Get_Scene())
		return;

	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Bmp(L"back_black_1920,1080"); // 전에 그려진 그림 덮어쓰기
	HDC hBackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"back_black_1920,1080_2"); // 새로 그릴 도화지

	BitBlt(hBackDC, 0, 0, WINCX, WINCY, hGroundDC, 0, 0, SRCCOPY);

	CSceneMgr::Get_Instance()->Render(hBackDC);
	CUiMgr::Get_Instance()->Render(hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackDC, 0, 0, SRCCOPY);

#pragma endregion
}

void CMainGame::Release()
{

#pragma region 개발자모드 (시연회할때 삭제해야함)

//#ifdef _DEBUG
//
//	FreeConsole();
//
//#endif // _DEBUG

#pragma endregion

	CObjMgr::Destroy();
	CUiMgr::Destroy();
	CLineMgr::Destroy();
	CKeyMgr::Destroy();
	CScrollMgr::Destroy();
	CBmpMgr::Destroy();
	CSceneMgr::Destroy();
	//CTileMgr::Destroy();
	CSoundMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);

}
