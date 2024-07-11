#include "pch.h"
#include "MobB1.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "Item_BluePotion.h"

CMobB1::CMobB1()
	: m_dwTime(999), m_bItemDrop(false)
{
}

CMobB1::~CMobB1()
{
}

void CMobB1::Initialize()
{
	m_tInfo.fCX = 90.f;
	m_tInfo.fCY = 183.f;

	m_fExp = 95;

	m_fMaxHp = 1000;
	m_fHp = m_fMaxHp;

	m_fPower = 15.f;

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Mob/MobB1_stand_left_0,11.bmp", L"MobB1_stand_left_0,11");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Mob/MobB1_hit_left_0.bmp", L"MobB1_hit_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Mob/MobB1_die_left_0,9.bmp", L"MobB1_die_left_0,9");

	m_eCurState = STAND;
	m_tFrame = { 0, 5, 0, 300, GetTickCount() };
	m_pFrameKey = L"MobB1_stand_left_0,11";
}

int CMobB1::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

#pragma region 플레이어 스킬에 맞으면 데미지 닳음

	if (m_fHp < 0)
	{
		while (!m_bItemDrop)
		{
			// 아이템
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_BluePotion>::Create(m_tInfo.fX, m_tInfo.fY));

			m_bItemDrop = true;
		}

		if (m_ePreState != DIE)
		{
			m_eCurState = DIE;
			m_pFrameKey = L"MobB1_die_left_0,9";
			m_dwTime = GetTickCount();

		}
		else if (m_dwTime + 1000 < GetTickCount())
		{
			m_pFrameKey = L"";
			m_bDead = true;
		}
	}
	else
	{

		bool bHit =
			CCollisionMgr::CheckObj_Multi(
				CObjMgr::Get_Instance()->Get_TypeObj(OBJ_SKILL),
				CObjMgr::Get_Instance()->Get_TypeObj(OBJ_MOB_B1));

		if (bHit)
		{
			m_eCurState = HIT;
			m_pFrameKey = L"MobB1_hit_left_0";
			m_dwTime = GetTickCount();

			m_fHp -= 50.f;
		}

	}



#pragma endregion

	__super::Update_Rect();

	return 0;
}

void CMobB1::Late_Update()
{
	Motion_Change();

	__super::Move_Frame();
}

void CMobB1::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, m_tRect.left + fScrollX, m_tRect.top + fScrollY,
	//	m_tRect.right + fScrollX, m_tRect.bottom + fScrollY);

	GdiTransparentBlt(
		// TO
		hDC,											// 도착할 DC
		m_tRect.left + fScrollX,
		m_tRect.top + fScrollY,							// 좌상단에서부터
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,								// 가로세로 이 길이만큼

		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,		// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * (int)m_tInfo.fCY,			// 몇행부터 세로 간격 얼만큼씩
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,								// 한 이미지당 가로세로 이만큼씩 잘라서

		// COLOR
		RGB(255, 0, 255)								// 제거할 색상값	
	);

}

void CMobB1::Release()
{
}

void CMobB1::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CMobB1::STAND:
			m_tFrame = { 0, 11, 0, 100, GetTickCount() };
			break;

		case CMobB1::HIT:
			m_tFrame = { 0, 0, 0, 100, GetTickCount() };
			break;

		case CMobB1::DIE:
			m_tFrame = { 0, 9, 0, 100, GetTickCount() };
			break;
		}
		m_ePreState = m_eCurState;
	}
}