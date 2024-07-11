#include "pch.h"
#include "DimensionPath.h"

#include "ObjMgr.h"
#include "LineMgr.h"
//#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

CDimensionPath::CDimensionPath()
{
}

CDimensionPath::~CDimensionPath()
{
	Release();
}

void CDimensionPath::Initialize()
{
	iTotalWidth = 1330;
	iTotalHeight = 750;

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Map/Bmp1_DimensionPath.bmp", L"Bmp1_DimensionPath");
	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(900.f, 0.f);
}

int CDimensionPath::Update()
{
	CLineMgr::Get_Instance()->Initialize(SCENEID::Scene1_DimensionPath);

	CObjMgr::Get_Instance()->Update();

	return 0;
}

void CDimensionPath::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CDimensionPath::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Bmp1_DimensionPath");

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	BitBlt(hDC, iScrollX, iScrollY, iTotalWidth, iTotalHeight, hMemDC, 0, 0, SRCCOPY);

	CObjMgr::Get_Instance()->Render(hDC);
}

void CDimensionPath::Release()
{
	Remove_All();

}
