#include "pch.h"
#include "ZeroTemple.h"

#include "ObjMgr.h"
#include "LineMgr.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "KeyMgr.h"

#include "AbstractFactory.h"
#include "NPC_Ragun.h"
#include "NPC_Chou.h"
#include "NPC_Cell.h"
#include "NPC_Pien.h"
#include "NPC_Dello.h"

#include "Portal.h"

#include "Item_OrangePotion.h"

CZeroTemple::CZeroTemple()
{
}

CZeroTemple::~CZeroTemple()
{
	Release();
}

void CZeroTemple::Initialize()
{
	iTotalWidth = 1366;
	iTotalHeight = 767;

	// 배경
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp0_ZeroTemple.bmp", L"Bmp0_ZeroTemple");

	// 브금
	CSoundMgr::Get_Instance()->PlayBGM(L"ZeroTemple.mp3", 1.f);

	// 포탈
	CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, CAbstractFactory<CPortal>::Create(683.f, 620.f));

	// NPC
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_Ragun>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_Chou>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_Cell>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_Pien>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_Dello>::Create());

	// 아이템
	CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_OrangePotion>::Create(500.f, 0.f));

	// 스폰
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 0.f);
}

int CZeroTemple::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene0_ZeroTemple);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CZeroTemple::Late_Update()
{
#pragma region 	포탈 이동으로 씬 전환

	bool bPortal = CCollisionMgr::CheckObj_Multi(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER)
		, CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PORTAL));

	if (bPortal == true &&
		CKeyMgr::Get_Instance()->Key_IN(VK_UP))
	{
		CSceneMgr::Get_Instance()->Scene_Change(Scene2_ThreeDoors);
		return;
	}

#pragma endregion

	CObjMgr::Get_Instance()->Late_Update();
}

void CZeroTemple::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp0_ZeroTemple");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CZeroTemple::Release()
{
	Remove_All();
	CSoundMgr::Get_Instance()->StopAll();
}
