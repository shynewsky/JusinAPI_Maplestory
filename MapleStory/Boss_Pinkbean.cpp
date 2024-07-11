#include "pch.h"
#include "Boss_Pinkbean.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

#include "PB_MusicNote.h"
#include "PB_Genesis.h"

#include "Item_PowerElixer.h"
#include "Item_Pinkbean_Hat.h"
#include "Item_Pinkbean_Hat.h"
#include "Item_Pinkbean_Suit.h"
#include "Item_Pinkbean_mark.h"
#include "Item_Blackbean_Mark.h"
#include "Item_BlackMage_Badge.h"
#include "Item_Pinkbean_Balloon.h"
#include "Item_Pinkbean_Belt.h"
#include "Item_Pinkbean_Cotton.h"
#include "Item_Pinkbean_Cup.h"
#include "Item_Pinkbean_Meat.h"
#include "Item_Pinkbean_Pet.h"
#include "Item_Pinkbean_Potion.h"
#include "Item_Pinkbean_Soul.h"


CBoss_Pinkbean::CBoss_Pinkbean()
	: m_dwTime(999), m_bMusicNote(false), m_bGenesis(false), m_bItemDrop(false)
{
}

CBoss_Pinkbean::~CBoss_Pinkbean()
{
}

void CBoss_Pinkbean::Initialize()
{
#pragma region 히트박스크기 및 중점좌표 위치

	m_fRectCX = 72.f;
	m_fRectCY = 86.f;

	m_fBltCX = 400.f;
	m_fBltCY = 310.f;

	m_fFootHeight = 62.f;

	m_fBltX = m_fBltCX * 0.5;
	m_fBltY = m_fBltCY - m_fFootHeight;

	m_tInfo = { 905.f, 553.f, m_fRectCX, m_fRectCY };

#pragma endregion

	m_fExp = 95;

	m_fMaxHp = 100000;
	m_fHp = m_fMaxHp;

	m_fPower = 15.f;

	__super::Update_Rect();

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_stand_0,5.bmp", L"boss_pinkbean_stand_0,5");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_move_0,7.bmp", L"boss_pinkbean_move_0,7");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_hit_0.bmp", L"boss_pinkbean_hit_0");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_returnAttack_0,19.bmp", L"boss_pinkbean_returnAttack_0,19");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_musicnote_0,19.bmp", L"boss_pinkbean_musicnote_0,19");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_genesis_0,14.bmp", L"boss_pinkbean_genesis_0,14");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_die_0,27.bmp", L"boss_pinkbean_die_0,27");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_musicnote_effect_0,7.bmp", L"boss_pinkbean_musicnote_effect_0,7");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Boss/boss_pinkbean_genesis_effect_0,15.bmp", L"boss_pinkbean_genesis_effect_0,15");

	m_eCurPB = PB_STAND;
	m_tFrame = { 0, 5, 0, 300, GetTickCount() };
	m_pFrameKey = L"boss_pinkbean_stand_0,5";
}

int CBoss_Pinkbean::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if(m_eCurPB != PB_DIE)
		Attack_Pattern();

#pragma region 플레이어 스킬에 맞으면 데미지 닳음

	bool bPSkill = CCollisionMgr::CheckObj_Multi(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_SKILL)
		, CObjMgr::Get_Instance()->Get_TypeObj(OBJ_BOSS));

	if (bPSkill == true &&
		m_ePrePB != PB_RETURNATTACK)
	{
		m_eCurPB = PB_HIT;
		m_pFrameKey = L"boss_pinkbean_hit_0";

		m_fHp -= 50.f;
	}

	if (m_fHp < 0)
	{
		while (!m_bItemDrop)
		{
			// 아이템
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_PowerElixer>::Create(200.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Hat>::Create(300.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Suit>::Create(400.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_mark>::Create(500.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Blackbean_Mark>::Create(600.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_BlackMage_Badge>::Create(700.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Balloon>::Create(800.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Belt>::Create(900.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Cotton>::Create(1000.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Cup>::Create(1100.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Meat>::Create(1200.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Pet>::Create(1300.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Potion>::Create(1400.f, 597.f));
			CObjMgr::Get_Instance()->Add_Object(OBJ_FIELDITEM, CAbstractFactory<CItem_Pinkbean_Soul>::Create(1500.f, 597.f));

			m_bItemDrop = true;
		}

		if (m_ePrePB != PB_DIE)
		{
			m_eCurPB = PB_DIE;
			m_pFrameKey = L"boss_pinkbean_die_0,27";
		}
		else if (m_dwTime + 5000 < GetTickCount())
		{
			m_pFrameKey = L"";
		}
	}

#pragma endregion

	__super::Update_Rect();

	return 0;
}

void CBoss_Pinkbean::Late_Update()
{
	Motion_Change();
	
	__super::Move_Frame();
}

void CBoss_Pinkbean::Render(HDC hDC)
{
	float fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	//Rectangle(hDC, 
	//	m_tInfo.fX + fScrollX - m_fBltX,
	//	m_tInfo.fY + fScrollY - m_fBltY,
	//	m_tInfo.fX + fScrollX - m_fBltX + m_fBltCX,
	//	m_tInfo.fY + fScrollY - m_fBltY + m_fBltCY
	//);

	GdiTransparentBlt(

		// TO
		hDC,											// 도착할 DC
		m_tInfo.fX + fScrollX - m_fBltX,
		m_tInfo.fY + fScrollY - m_fBltY,				// 좌상단에서부터
		m_fBltCX,
		m_fBltCY,										// 가로세로 이 길이만큼

		// FROM
		hMemDC,											// 출발할 DC
		m_tFrame.iFrameStart * m_fBltCX,				// 몇열부터 가로 간격 얼만큼씩	
		m_tFrame.iMotion * m_fBltCY,					// 몇행부터 세로 간격 얼만큼씩
		m_fBltCX,
		m_fBltCY,										// 한 이미지당 가로세로 이만큼씩 잘라서

		// Color
		RGB(255, 0, 255)								// 제거할 색상값	
	);
}

void CBoss_Pinkbean::Release()
{
}

void CBoss_Pinkbean::Attack_Pattern()
{
	switch (m_dwTime % 5)
	{
	case 0:
		m_eCurPB = PB_MUSICNOTE;
		m_pFrameKey = L"boss_pinkbean_musicnote_0,19";
		while (!m_bMusicNote)
		{
			Skill_MusicNote();
			m_bMusicNote = true;
		}
		if (m_dwTime + 1900 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			m_bMusicNote = false;
		}
		break;

	case 1:
		m_eCurPB = PB_RETURNATTACK;
		m_pFrameKey = L"boss_pinkbean_returnAttack_0,19";
		Skill_ReturnAttack();
		if (m_dwTime + 1900 < GetTickCount())
		{
			m_dwTime = GetTickCount();
		}
		break;

	case 2:
		m_eCurPB = PB_GENESIS;
		m_pFrameKey = L"boss_pinkbean_genesis_0,14";
		while (!m_bGenesis)
		{
			Skill_Genesis();
			m_bGenesis = true;
		}
		if (m_dwTime + 1400 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			m_bGenesis = false;
		}
		break;

	default:
		m_eCurPB = PB_STAND;
		m_pFrameKey = L"boss_pinkbean_stand_0,5";
		if (m_dwTime + 4000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
		}
		break;
	}
}

void CBoss_Pinkbean::Motion_Change()
{
	if (m_ePrePB != m_eCurPB)
	{
		switch (m_eCurPB)
		{
		case CBoss_Pinkbean::PB_MUSICNOTE:
			m_tFrame = { 0, 19, 0, 100, GetTickCount() };
			break;

		case CBoss_Pinkbean::PB_RETURNATTACK:
			m_tFrame = { 0, 19, 0, 100, GetTickCount() };
			break;

		case CBoss_Pinkbean::PB_GENESIS:
			m_tFrame = { 0, 14, 0, 100, GetTickCount() };
			break;

		case CBoss_Pinkbean::PB_DIE:
			m_tFrame = { 0, 27, 0, 100, GetTickCount() };
			break;

		case CBoss_Pinkbean::PB_STAND:
			m_tFrame = { 0, 5, 0, 200, GetTickCount() };
			break;

		case CBoss_Pinkbean::PB_HIT:
			m_tFrame = { 0, 0, 0, 200, GetTickCount() };
			break;
		}
		m_ePrePB = m_eCurPB;
	}
}

void CBoss_Pinkbean::Skill_Genesis()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_BSKILL,
		CAbstractFactory<CPB_Genesis>::Create(m_tInfo.fX, 672.f));
}

void CBoss_Pinkbean::Skill_MusicNote()
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_BSKILL,
		CAbstractFactory<CPB_MusicNote>::Create(m_tInfo.fX - 400.f, 672.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_BSKILL,
		CAbstractFactory<CPB_MusicNote>::Create(m_tInfo.fX - 200.f, 672.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_BSKILL,
		CAbstractFactory<CPB_MusicNote>::Create(m_tInfo.fX, 672.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_BSKILL,
		CAbstractFactory<CPB_MusicNote>::Create(m_tInfo.fX + 200.f, 672.f));

	CObjMgr::Get_Instance()->Add_Object(OBJ_BSKILL,
		CAbstractFactory<CPB_MusicNote>::Create(m_tInfo.fX + 400.f, 672.f));

}

void CBoss_Pinkbean::Skill_ReturnAttack()
{

	bool bPSkill = CCollisionMgr::CheckObj_Multi(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_SKILL)
		, CObjMgr::Get_Instance()->Get_TypeObj(OBJ_BOSS));

	if (bPSkill == true)
	{
		CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_PLAYER).front()->Set_Hp(-50.f);
	}

}
