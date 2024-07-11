#include "pch.h"
#include "TimeRoad1.h"

#include "ObjMgr.h"
#include "LineMgr.h"
//#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CTimeRoad1::CTimeRoad1()
{
}

CTimeRoad1::~CTimeRoad1()
{
	Release();
}

void CTimeRoad1::Initialize()
{
	iTotalWidth = 1993;
	iTotalHeight = 1591;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp3_TimeRoad1.bmp", L"Bmp3_TimeRoad1");
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(400.f, 100.f);
}

int CTimeRoad1::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene3_TimeRoad1);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CTimeRoad1::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CTimeRoad1::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp3_TimeRoad1");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CTimeRoad1::Release()
{
	Remove_All();

}
