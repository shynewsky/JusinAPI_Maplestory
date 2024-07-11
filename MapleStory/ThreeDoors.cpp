#include "pch.h"
#include "ThreeDoors.h"

#include "ObjMgr.h"
#include "LineMgr.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SoundMgr.h"

#include "AbstractFactory.h"
#include "Portal2.h"

#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#include "MobA1.h"
#include "MobB1.h"
#include "MobC1.h"

CThreeDoors::CThreeDoors()
{
}

CThreeDoors::~CThreeDoors()
{
	Release();
}

void CThreeDoors::Initialize()
{
	iTotalWidth = 4371;
	iTotalHeight = 780;

	// ¹è°æ
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp2_ThreeDoors.bmp", L"Bmp2_ThreeDoors");

	// ºê±Ý
	CSoundMgr::Get_Instance()->PlayBGM(L"ThreeDoors.mp3", 1.f);

	// Æ÷Å»
	CObjMgr::Get_Instance()->Add_Object(OBJ_PORTAL, CAbstractFactory<CPortal2>::Create(2590.f, 597.f));

	// ½ºÆù
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(500.f, 0.f);

	// ¸÷
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOB_A1, CAbstractFactory<CMobA1>::Create(700.f, 597.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOB_B1, CAbstractFactory<CMobB1>::Create(900.f, 597.f));
	CObjMgr::Get_Instance()->Add_Object(OBJ_MOB_C1, CAbstractFactory<CMobC1>::Create(1100.f, 597.f));
}

int CThreeDoors::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene2_ThreeDoors);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CThreeDoors::Late_Update()
{
#pragma region 	Æ÷Å» ÀÌµ¿À¸·Î ¾À ÀüÈ¯

	bool bPortal = CCollisionMgr::CheckObj_Multi(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER)
		, CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PORTAL));

	if (bPortal == true &&
		CKeyMgr::Get_Instance()->Key_IN(VK_UP))
	{
		CSceneMgr::Get_Instance()->Scene_Change(Scene6_ForgottenDusk);
		return;
	}

#pragma endregion

	CObjMgr::Get_Instance()->Late_Update();
}

void CThreeDoors::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp2_ThreeDoors");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CThreeDoors::Release()
{
	Remove_All();
	CSoundMgr::Get_Instance()->StopAll();
}
