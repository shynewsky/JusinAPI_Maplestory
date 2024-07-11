#include "pch.h"
#include "BossUI_EnterBox.h"

#include "BmpMgr.h"

#include "UIMgr.h"
#include "AbstractFactoryUI.h"
#include "BossUI_Bt1_Normal.h"
#include "BossUI_Bt2_Chaos.h"

CBossUI_EnterBox::CBossUI_EnterBox()
{
}

CBossUI_EnterBox::~CBossUI_EnterBox()
{
	Release();
}

void CBossUI_EnterBox::Initialize()
{
	m_tInfo = { 0.f, 300.f, 802.f, 602.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BossUI/BossUI_EnterBox_0.bmp", L"BossUI_EnterBox_0");
	m_pFrameKey = L"BossUI_EnterBox_0";

	CUiMgr::Get_Instance()->Add_Object(UI_PBUTTON, CAbstractFactoryUI<CBossUI_Bt1_Normal>::Create(600.f, 450.f));
	CUiMgr::Get_Instance()->Add_Object(UI_PBUTTON, CAbstractFactoryUI<CBossUI_Bt2_Chaos>::Create(600.f, 500.f));
}

int CBossUI_EnterBox::Update()
{
	return 0;
}

void CBossUI_EnterBox::Late_Update()
{
}

void CBossUI_EnterBox::Render(HDC hDC)
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
		// COLOR
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CBossUI_EnterBox::Release()
{
}
