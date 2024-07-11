#include "pch.h"
#include "InventoryUI.h"

#include "BmpMgr.h"
#include "AbstractFactoryUI.h"
#include "ItemSlotUI.h"
#include "UIMgr.h"

#include "KeyMgr.h"
#include "Mouse.h"
#include "CollisionMgr.h"

#include "Player.h"
#include "ObjMgr.h"

CInventoryUI::CInventoryUI()
	: m_iStartSlot(-1), m_iEndSlot(-1)
	, m_iPreItemCount(-1), m_iCurItemCount(-1)
{
	m_vecSlot.reserve(24);
}

CInventoryUI::~CInventoryUI()
{
	Release();
}

void CInventoryUI::Initialize()
{
#pragma region 베이스

	m_tInfo = { 550.f, 300.f, 199.f, 377.f };

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/UI/ItemUI/ItemUI_Base_0.bmp", L"ItemUI_Base_0");

	m_pFrameKey = L"ItemUI_Base_0";

#pragma endregion

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			CUi* pSlot = CAbstractFactoryUI<CItemSlotUI>::Create(
				m_tInfo.fX + 7.f + 42.f * j,
				m_tInfo.fY - 118.5f + 42.f * i
			);

			CUiMgr::Get_Instance()->Add_Object(UI_ISLOT, pSlot);

			m_vecSlot.push_back(pSlot);
		}
	}
}

int CInventoryUI::Update()
{
	Set_ItemSlot();

	Check_Click();

	return 0;
}

void CInventoryUI::Late_Update()
{

}

void CInventoryUI::Render(HDC hDC)
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

	for (auto& Slot : m_vecSlot)
	{
		Slot->Render(hDC);
	}
}

void CInventoryUI::Release()
{
}

void CInventoryUI::Set_ItemSlot()
{
	list<CObj>& pInventory = CObjMgr::Get_Instance()->Get_Player()->Get_MyItemList();
	m_iCurItemCount = pInventory.size();

	if (m_iPreItemCount != m_iCurItemCount )
	{
		if (pInventory.size() != 0) // 들어있는 아이템이 있을때
		{
			for (auto& Item : pInventory) // 아이템을
			{
				for (auto& Slot : m_vecSlot) // 빈 슬롯에 넣는다
				{
					if (m_iPreItemCount > 0)
					{
						m_iPreItemCount--;
						break;
					}

					if (Slot->Get_FrameKey() == L"")
					{
						ITEMNAME eItemName = Item.Get_ItemName();
						Slot->Set_FrameKey(Find_FrameKey(eItemName));

						m_iPreItemCount--;
						break;
					}
				}
			}

//#pragma region 개발자모드 (시연회할때 삭제해야함)
//#ifdef _DEBUG
//			if (m_dwConsole + 1000 < GetTickCount())
//			{
//				cout << m_iCountDifference << endl;
//				m_dwConsole = GetTickCount();
//			}
//#endif
//#pragma endregion

		}

		m_iPreItemCount = m_iCurItemCount;
	}
}

TCHAR* CInventoryUI::Find_FrameKey(ITEMNAME eID)
{
	switch (eID)
	{
	case INAME_PowerElixer:
		return L"Item_PowerElixir_slot";
		break;

	case INAME_RedPotion:
		return L"Item_RedPotion_slot";
		break;

	case INAME_BluePotion:
		return L"Item_BluePotion_slot";
		break;

	case INAME_OrangePotion:
		return L"Item_OrangePotion_slot";
		break;

	case INAME_WhitePotion:
		return L"Item_WhitePotion_slot";
		break;

	case INAME_PinkbeanHat:
		return L"Item_Pinkbean_hat_slot";
		break;

	case INAME_PinkbeanSuit:
		return L"Item_Pinkbean_suit_slot";
		break;

	case INAME_PinkbeanMark:
		return L"Item_Pinkbean_mark_slot";
		break;

	case INAME_BlackbeanMark:
		return L"Item_Blackbean_drop";
		break;

	case INAME_BlackMageBadge:
		return L"Item_BlackMage_badge_slot";
		break;

	case INAME_PinkbeanBalloon:
		return L"Item_Pinkbean_balloon_slot";
		break;

	case INAME_PinkbeanBelt:
		return L"Item_Pinkbean_belt_slot";
		break;

	case INAME_PinkbeanCotton:
		return L"Item_Pinkbean_cotton_slot";
		break;

	case INAME_PinkbeanCup:
		return L"Item_Pinkbean_cup_slot";
		break;

	case INAME_PinkbeanMeat:
		return L"Item_Pinkbean_meat_slot";
		break;

	case INAME_PinkbeanPet:
		return L"Item_Pinkbean_pet_slot";
		break;

	case INAME_PinkbeanPotion:
		return L"Item_Pinkbean_potion_slot";
		break;

	case INAME_PinkbeanSoul:
		return L"Item_Pinkbean_soul_slot";
		break;
	}

	return nullptr;
}

void CInventoryUI::Check_Click()
{
	//int iSlot = CCollisionMgr::SlotClick_Rect(
	//			CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_MOUSE),
	//			m_vecSlot);

	//if (m_iStartSlot == -1 && 
	//	m_vecSlot[iSlot]->Get_FrameKey() != L"" &&
	//	CKeyMgr::Get_Instance()->Key_IN(VK_LBUTTON) &&
	//	m_dwTime + 1000 < GetTickCount())
	//{
	//	m_iStartSlot = iSlot;
	//	m_dwTime = GetTickCount();
	//}
	//else if (m_iStartSlot != -1 &&
	//	CKeyMgr::Get_Instance()->Key_IN(VK_LBUTTON) &&
	//	m_dwTime + 1000 < GetTickCount())
	//{
	//	m_iEndSlot = iSlot;

	//	swap(m_vecSlot[m_iStartSlot], m_vecSlot[m_iEndSlot]);

	//	m_dwTime = GetTickCount();

	//	m_iStartSlot = -1;
	//	m_iEndSlot = -1;
	//}
}

