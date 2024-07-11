#include "pch.h"
#include "MainUI_HpTpGauge1.h"

#include "BmpMgr.h"
#include "ObjMgr.h"

CMainUI_HpTpGauge1::CMainUI_HpTpGauge1()
{
}

CMainUI_HpTpGauge1::~CMainUI_HpTpGauge1()
{
	Release();
}

void CMainUI_HpTpGauge1::Initialize()
{
	m_tInfo = { 436.f, 554.5f, 141.f, 13.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_HpTPGauge1_0.bmp", L"BottomUI_HpTPGauge1_0");
	m_pFrameKey = L"BottomUI_HpTPGauge1_0";
}

int CMainUI_HpTpGauge1::Update()
{
	m_tInfo.fCX = 141.f *
		CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_PLAYER).front()->Get_Hp() /
		CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_PLAYER).front()->Get_MaxHp();

	return 0;
}

void CMainUI_HpTpGauge1::Late_Update()
{
}

void CMainUI_HpTpGauge1::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(
		// TO
		hDC,										// 도착할 DC
		m_tRect.left,
		m_tRect.top,								// 좌상단에서부터
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,							// 가로세로 이 길이만큼
		// FROM
		hMemDC,										// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,		// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,							// 한 이미지당 가로세로 이만큼씩 잘라서
		// COLOR
		RGB(255, 0, 255)							// 제거할 색상값	
	);
}

void CMainUI_HpTpGauge1::Release()
{
}
