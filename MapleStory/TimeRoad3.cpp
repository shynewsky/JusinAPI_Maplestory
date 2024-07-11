#include "pch.h"
#include "TimeRoad3.h"

#include "ObjMgr.h"
#include "LineMgr.h"
//#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CTimeRoad3::CTimeRoad3()
{
}

CTimeRoad3::~CTimeRoad3()
{
	Release();
}

void CTimeRoad3::Initialize()
{
	iTotalWidth = 2398;
	iTotalHeight = 1487;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp5_TimeRoad3.bmp", L"Bmp5_TimeRoad3");
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 0.f);
}

int CTimeRoad3::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene5_TimeRoad3);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CTimeRoad3::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CTimeRoad3::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp5_TimeRoad3");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CTimeRoad3::Release()
{
	Remove_All();

}
