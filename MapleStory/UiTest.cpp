#include "pch.h"
#include "UiTest.h"

#include "BmpMgr.h"

CUiTest::CUiTest()
{
}

CUiTest::~CUiTest()
{
	Release();
}

void CUiTest::Initialize()
{
	m_tInfo = { 400.f, 595.f, 800.f, 10.f };

	__super::Update_Rect();

#pragma region 애니메이션

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_ExpBar_0.bmp", L"BottomUI_ExpBar_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_ExpGauge_0.bmp", L"BottomUI_ExpGauge_0");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_HpTpBar1_0.bmp", L"BottomUI_HpTpBar1_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_HpTPGauge1_0.bmp", L"BottomUI_HpTPGauge1_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_HpTPGauge2_0.bmp", L"BottomUI_HpTPGauge2_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_HpTpBar2_0.bmp", L"BottomUI_HpTpBar2_0");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_AssistHpBar1_0.bmp", L"BottomUI_AssistHpBar1_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_AssistHpBar2_0.bmp", L"BottomUI_AssistHpBar2_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_AssistHpGauge1_0.bmp", L"BottomUI_AssistHpGauge1_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_AssistHpGauge2_0.bmp", L"BottomUI_AssistHpGauge2_0");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu0_cash_0123.bmp", L"BottomUI_menu0_cash_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu1_event_0123.bmp", L"BottomUI_menu1_event_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu2_char_0123.bmp", L"BottomUI_menu2_char_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu3_commu_0123.bmp", L"BottomUI_menu3_commu_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu4_setting_0123.bmp", L"BottomUI_menu4_setting_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BottomUI/BottomUI_menu5_option_0123.bmp", L"BottomUI_menu5_option_0123");

	m_tFrame = { 0, 0, 0, 0 , GetTickCount() };
	m_pFrameKey = L"BottomUI_ExpBar_0";

#pragma endregion


}

int CUiTest::Update()
{
	return 0;
}

void CUiTest::Late_Update()
{
	//__super::Move_Frame();
}

void CUiTest::Render(HDC hDC)
{
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

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

void CUiTest::Release()
{
}
