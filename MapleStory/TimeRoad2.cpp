#include "pch.h"
#include "TimeRoad2.h"

#include "ObjMgr.h"
#include "LineMgr.h"
//#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CTimeRoad2::CTimeRoad2()
{
}

CTimeRoad2::~CTimeRoad2()
{
	Release();
}

void CTimeRoad2::Initialize()
{
	iTotalWidth = 1598;
	iTotalHeight = 1519;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp4_TimeRoad2.bmp", L"Bmp4_TimeRoad2");
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 100.f);
}

int CTimeRoad2::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene4_TimeRoad2);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CTimeRoad2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CTimeRoad2::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp4_TimeRoad2");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CTimeRoad2::Release()
{
	Remove_All();

}
