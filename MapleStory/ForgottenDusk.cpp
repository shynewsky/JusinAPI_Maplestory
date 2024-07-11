#include "pch.h"
#include "ForgottenDusk.h"

#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

#include "AbstractFactory.h"
#include "NPC_EnterBoss.h"

CForgottenDusk::CForgottenDusk()
{
}

CForgottenDusk::~CForgottenDusk()
{
	Release();
}

void CForgottenDusk::Initialize()
{
	iTotalWidth = 1550;
	iTotalHeight = 789;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp6_ForgottenDusk.bmp", L"Bmp6_ForgottenDusk");

	CSoundMgr::Get_Instance()->PlayBGM(L"ForgottenDusk.mp3", 1.f);

	CObjMgr::Get_Instance()->Add_Object(OBJ_NPC, CAbstractFactory<CNPC_EnterBoss>::Create());

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 0.f);
}

int CForgottenDusk::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene6_ForgottenDusk);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CForgottenDusk::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CForgottenDusk::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp6_ForgottenDusk");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CForgottenDusk::Release()
{
	Remove_All();
	CSoundMgr::Get_Instance()->StopAll();
}
