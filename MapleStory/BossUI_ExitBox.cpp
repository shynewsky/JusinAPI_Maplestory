#include "pch.h"
#include "BossUI_ExitBox.h"

#include "BmpMgr.h"

#include "UIMgr.h"
#include "AbstractFactoryUI.h"
#include "BossUI_Bt1_Yes.h"
#include "BossUI_Bt2_No.h"

CBossUI_ExitBox::CBossUI_ExitBox()
{
}

CBossUI_ExitBox::~CBossUI_ExitBox()
{
	Release();
}

void CBossUI_ExitBox::Initialize()
{
	m_tInfo = { 140.f, 300.f, 519.f, 200.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/BossUI/TalkUI_boxExitBoss_0.bmp", L"TalkUI_boxExitBoss_0");
	m_pFrameKey = L"TalkUI_boxExitBoss_0";

	CUiMgr::Get_Instance()->Add_Object(UI_PBUTTON, CAbstractFactoryUI<CBossUI_Bt1_Yes>::Create(520.f, 385.f));
	CUiMgr::Get_Instance()->Add_Object(UI_PBUTTON, CAbstractFactoryUI<CBossUI_Bt2_No>::Create(585.f, 385.f));

}

int CBossUI_ExitBox::Update()
{
	return 0;
}

void CBossUI_ExitBox::Late_Update()
{
}

void CBossUI_ExitBox::Render(HDC hDC)
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

void CBossUI_ExitBox::Release()
{
}
