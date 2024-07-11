#include "pch.h"
#include "MainUi_ExpGauge.h"

#include "BmpMgr.h"
#include "ObjMgr.h"

CMainUi_ExpGauge::CMainUi_ExpGauge()
{
}

CMainUi_ExpGauge::~CMainUi_ExpGauge()
{
	Release();
}

void CMainUi_ExpGauge::Initialize()
{
	m_tInfo = { 16.f, 595.f, 784.f, 7.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_ExpGauge_0.bmp", L"BottomUI_ExpGauge_0");
	m_pFrameKey = L"BottomUI_ExpGauge_0";
}

int CMainUi_ExpGauge::Update()
{
	m_tInfo.fCX = 784.f *
		CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_PLAYER).front()->Get_Exp() /
		CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_PLAYER).front()->Get_MaxExp();
			
	return 0;
}

void CMainUi_ExpGauge::Late_Update()
{
}

void CMainUi_ExpGauge::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(
		// TO
		hDC,											// 도착할 DC
		m_tRect.left, m_tRect.top,						// 좌상단에서부터
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,				// 가로세로 이 길이만큼
		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX, (int)m_tInfo.fCY,				// 한 이미지당 가로세로 이만큼씩 잘라서
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CMainUi_ExpGauge::Release()
{
}
