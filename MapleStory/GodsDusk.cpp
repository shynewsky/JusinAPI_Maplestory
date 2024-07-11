#include "pch.h"
#include "GodsDusk.h"

#include "AbstractFactory.h"
#include "AbstractFactoryUI.h"

#include "ObjMgr.h"
#include "UIMgr.h"
#include "LineMgr.h"
//#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "NPC_ExitBoss.h"
#include "NPC_Kirstern.h"

#include "Boss_Pinkbean.h"

#include "BossUI_HpBar.h"
#include "bossui_HpGauge.h"

CGodsDusk::CGodsDusk()
{
}

CGodsDusk::~CGodsDusk()
{
	Release();
}

void CGodsDusk::Initialize()
{
	iTotalWidth = 1788;
	iTotalHeight = 829;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp7_GodsDusk.bmp", L"Bmp7_GodsDusk");

	CSoundMgr::Get_Instance()->PlayBGM(L"GodsDusk.mp3", 1.f);

	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_ExitBoss>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_Kirstern>::Create());

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1100.f, 600.f);

	if (CSceneMgr::Get_Instance()->Get_PBVideo() == true)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_BOSS, CAbstractFactory<CBoss_Pinkbean>::Create());

		CUiMgr::Get_Instance()->Add_Object(UI_BOSS, CAbstractFactoryUI<CBossUI_HpBar>::Create());
		CUiMgr::Get_Instance()->Add_Object(UI_BOSS, CAbstractFactoryUI<CBossUI_HpGauge>::Create());
	}
}

int CGodsDusk::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene7_GodsDusk);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CGodsDusk::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CGodsDusk::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp7_GodsDusk");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CGodsDusk::Release()
{
	Remove_All();

	CSoundMgr::Get_Instance()->StopAll();
}
