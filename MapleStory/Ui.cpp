#include "pch.h"
#include "Ui.h"

#include "UIMgr.h"

CUi::CUi()
	: m_fSpeed(0.f)/*, m_bDead(false)*/
	, m_fRectCX(0.f), m_fRectCY(0.f), m_fBltCX(0.f), m_fBltCY(0.f), m_fBltX(0.f), m_fBltY(0.f), m_fFootHeight(0.f)
	/*, m_fExp(0.f), m_fMaxExp(0.f), m_fHp(0.f), m_fMaxHp(0.f), m_fTp(0.f), m_fMaxTp(0.f), m_fPower(0.f)*/
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CUi::~CUi()
{
}

void CUi::Update_Rect()
{
	//m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.left = long(m_tInfo.fX);
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	//m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.right = long(m_tInfo.fX + m_tInfo.fCX);
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}

void CUi::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CUi::Remove_PopUpUI()
{
	list<CUi*>& PopupList = CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_POPUP);
	list<CUi*>& PButtonList = CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_PBUTTON);

	for (auto& PopupUI : PopupList)
	{
		Safe_Delete<CUi*>(PopupUI);
	}
	PopupList.clear();

	for (auto& PButton : PButtonList)
	{
		Safe_Delete<CUi*>(PButton);
	}
	PButtonList.clear();
}

void CUi::Remove_InventoryUI()
{
	list<CUi*>& InvenList = CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_INVEN);
	list<CUi*>& ISlotList = CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_ISLOT);

	for (auto& InvenUI : InvenList)
	{
		Safe_Delete<CUi*>(InvenUI);
	}
	InvenList.clear();

	for (auto& ISlot : ISlotList)
	{
		Safe_Delete<CUi*>(ISlot);
	}
	ISlotList.clear();

}

