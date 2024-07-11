#include "pch.h"
#include "Player.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "SceneMgr.h"

#include "SKill_moonStrike.h"
#include "Skill_flashAssaulter.h"
#include "Skill_upperSlash.h"
#include "Skill_frontSlash.h"

#include "UIMgr.h"
#include "AbstractFactoryUI.h"
#include "InventoryUI.h"

#include "PinkFox.h"
#include "YellowFox.h"
#include "BlueFox.h"

CPlayer::CPlayer()
	: m_bJump(false), m_fPower(0.f), m_fTime(0.f)
	, m_fAssistHp(0.f), m_fAssistTp(0.f), m_dwTime(GetTickCount())
	, m_bInvenOpen(false), m_dwOpen(GetTickCount())
	, m_dwConsole(GetTickCount())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{

#pragma region 알파 애니메이션

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stand1_left_0121.bmp", L"alpha_stand1_left_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stand1_right_0121.bmp", L"alpha_stand1_right_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_walk1_left_0123.bmp", L"alpha_walk1_left_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_walk1_right_0123.bmp", L"alpha_walk1_right_0123");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_rope_01.bmp", L"alpha_rope_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_ladder_01.bmp", L"alpha_ladder_01");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_prone_left_0.bmp", L"alpha_prone_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_prone_right_0.bmp", L"alpha_prone_right_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_proneStab_left_01.bmp", L"alpha_proneStab_left_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_proneStab_right_01.bmp", L"alpha_proneStab_right_01");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_sit_left_0.bmp", L"alpha_sit_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_sit_right_0.bmp", L"alpha_sit_right_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_jump_left_0.bmp", L"alpha_jump_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_jump_right_0.bmp", L"alpha_jump_right_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_heal_left_012.bmp", L"alpha_heal_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_heal_right_012.bmp", L"alpha_heal_right_012");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stabO1_left_01.bmp", L"alpha_stabO1_left_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stabO1_right_01.bmp", L"alpha_stabO1_right_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stabO2_left_01.bmp", L"alpha_stabO2_left_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stabO2_right_01.bmp", L"alpha_stabO2_right_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stabOF_left_012.bmp", L"alpha_stabOF_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_stabOF_right_012.bmp", L"alpha_stabOF_right_012");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingT1_left_012.bmp", L"alpha_swingT1_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingT1_right_012.bmp", L"alpha_swingT1_right_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingT2_left_012.bmp", L"alpha_swingT2_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingT2_right_012.bmp", L"alpha_swingT2_right_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingT3_left_012.bmp", L"alpha_swingT3_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingT3_right_012.bmp", L"alpha_swingT3_right_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingTF_left_0123.bmp", L"alpha_swingTF_left_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_swingTF_right_0123.bmp", L"alpha_swingTF_right_0123");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_alert_left_0121.bmp", L"alpha_alert_left_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_alert_right_0121.bmp", L"alpha_alert_right_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/AlphaMotion/alpha_dead_0.bmp", L"alpha_dead_0");

#pragma endregion

#pragma region 베타 애니메이션

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stand1_left_0121.bmp", L"beta_stand1_left_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stand1_right_0121.bmp", L"beta_stand1_right_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_walk1_left_0123.bmp", L"beta_walk1_left_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_walk1_right_0123.bmp", L"beta_walk1_right_0123");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_rope_01.bmp", L"beta_rope_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_ladder_01.bmp", L"beta_ladder_01");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_prone_left_0.bmp", L"beta_prone_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_prone_right_0.bmp", L"beta_prone_right_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_proneStab_left_01.bmp", L"beta_proneStab_left_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_proneStab_right_01.bmp", L"beta_proneStab_right_01");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_sit_left_0.bmp", L"beta_sit_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_sit_right_0.bmp", L"beta_sit_right_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_jump_left_0.bmp", L"beta_jump_left_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_jump_right_0.bmp", L"beta_jump_right_0");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_heal_left_012.bmp", L"beta_heal_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_heal_right_012.bmp", L"beta_heal_right_012");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stabO1_left_01.bmp", L"beta_stabO1_left_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stabO1_right_01.bmp", L"beta_stabO1_right_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stabO2_left_01.bmp", L"beta_stabO2_left_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stabO2_right_01.bmp", L"beta_stabO2_right_01");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stabOF_left_012.bmp", L"beta_stabOF_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_stabOF_right_012.bmp", L"beta_stabOF_right_012");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingT1_left_012.bmp", L"beta_swingT1_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingT1_right_012.bmp", L"beta_swingT1_right_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingT2_left_012.bmp", L"beta_swingT2_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingT2_right_012.bmp", L"beta_swingT2_right_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingT3_left_012.bmp", L"beta_swingT3_left_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingT3_right_012.bmp", L"beta_swingT3_right_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingTF_left_0123.bmp", L"beta_swingTF_left_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_swingTF_right_0123.bmp", L"beta_swingTF_right_0123");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_alert_left_0121.bmp", L"beta_alert_left_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_alert_right_0121.bmp", L"beta_alert_right_0121");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/BetaMotion/beta_dead_0.bmp", L"beta_dead_0");

#pragma endregion

#pragma region 알파 스킬이펙트

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/alpha_skill0_moonStrike_effect_left_01234.bmp", L"alpha_skill0_moonStrike_effect_left_01234");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/alpha_skill0_moonStrike_effect_right_01234.bmp", L"alpha_skill0_moonStrike_effect_right_01234");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/alpha_skill4_flashAssaulter_effect_left_01234.bmp", L"alpha_skill4_flashAssaulter_effect_left_01234");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/alpha_skill4_flashAssaulter_effect_right_01234.bmp", L"alpha_skill4_flashAssaulter_effect_right_01234");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/HitEffect/alpha_skill0_hit_moonStrike_0123.bmp", L"alpha_skill0_hit_moonStrike_0123");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/HitEffect/alpha_skill4_hit_flashAssaulter_0123.bmp", L"alpha_skill4_hit_flashAssaulter_0123");

#pragma endregion

#pragma region 베타 스킬이펙트

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/beta_skill0_upperSlash_effect_left_0123456.bmp", L"beta_skill0_upperSlash_effect_left_0123456");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/beta_skill0_upperSlash_effect_right_0123456.bmp", L"beta_skill0_upperSlash_effect_right_0123456");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/beta_skill4_frontSlash_effect_left_012345.bmp", L"beta_skill4_frontSlash_effect_left_012345");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/SkillEffect/beta_skill4_frontSlash_effect_right_012345.bmp", L"beta_skill4_frontSlash_effect_right_012345");

	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/HitEffect/beta_skill0_hit_upperSlash_012.bmp", L"beta_skill0_hit_upperSlash_012");
	CBmpMgr::Get_Instance()->Add_Bmp(L"../Data/Player/HitEffect/beta_skill4_hit_frontSlash_012.bmp", L"beta_skill4_hit_frontSlash_012");

#pragma endregion

	//--------------------------------------------------

#pragma region 히트박스크기 및 중점좌표 위치

	m_fRectCX = 54.f;
	m_fRectCY = 74.f;

	m_fBltCX = 300.f;
	m_fBltCY = 185.f;

	m_fFootHeight = 45.f;

	m_fBltX = m_fBltCX * 0.5;
	m_fBltY = m_fBltCY - m_fFootHeight;

	m_tInfo = { 300.f, 0.f, m_fRectCX, m_fRectCY };

#pragma endregion

#pragma region 그외 스탯

	m_fSpeed = 5.f; // 알바베타 속도 다름 --> 나중에 고치기

	m_fMaxExp = 100;
	m_fExp = 70;

	m_fMaxHp = 10000;
	m_fHp = m_fMaxHp;
	m_fAssistHp = m_fMaxHp;

	m_fMaxTp = 130;
	m_fTp = m_fMaxTp;
	m_fAssistTp = m_fMaxTp;

	m_fPower = 15.f;

#pragma endregion

	CScrollMgr::Get_Instance()->Set_ScrollY(-150.f);

	m_eDir = DIR_RIGHT;
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	// 스폰
	list<CObj*> petList = CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PET);
	for (auto& pet : petList)
	{
		pet->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	}


	Key_Input();

	Lose_HP();

	Collect_Item();

	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	Jump(); // 점프든 아니든 일단 선위에 세우고본다

	Offset();

	FrameKey_Change(); // --> Cur기준

	Zero_Change(); // 태그시스템 --> PreZero = CurZero 대입

	Motion_Change(); // FRAME 값 변경하고 --> PreState = CurState 대입

	__super::Move_Frame(); // 변경된 FRAME 값에 새로 애니메이션 구현
}

void CPlayer::Render(HDC hDC)
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

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{

	if (m_eCurState == ST_DEAD)
		return;

#pragma region 스킬 (QWAS)

	if (CKeyMgr::Get_Instance()->Key_IN('Q'))
	{
		m_eCurZero = ZERO_ALPHA;
		m_eCurState = ST_STABF;
		Skill_Alpha_moonStrike(m_eDir);
	}

	else if (CKeyMgr::Get_Instance()->Key_IN('W'))
	{
		if (m_fTp > 0.f)
		{
			m_fTp -= 1.f;
			m_eCurZero = ZERO_ALPHA;
			m_eCurState = ST_STABF;
			Skill_Alpha_flashAssaulter(m_eDir);
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_IN('A'))
	{
		m_eCurZero = ZERO_BETA;
		m_eCurState = ST_SWING3;
		Skill_Beta_upperSlash(m_eDir);
	}

	else if (CKeyMgr::Get_Instance()->Key_IN('S'))
	{
		if (m_fTp > 0.f)
		{
			m_fTp -= 1.f;
			m_eCurZero = ZERO_BETA;
			m_eCurState = ST_SWING3;
			Skill_Beta_frontSlash(m_eDir);
		}
	}

#pragma endregion

#pragma region 줍기

	else if (CKeyMgr::Get_Instance()->Key_IN('Z'))
	{
		// 주변에 아이템이 있으며		
		bool bItem = 
			CCollisionMgr::CheckObj_Multi(
			CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER),
			CObjMgr::Get_Instance()->Get_TypeObj(OBJ_FIELDITEM));

		list<CObj>& pInventory = CObj::Get_MyItemList();

		if (bItem == true &&
			pInventory.size() <= 24)
		{
			// 아이템 주워서
			CObj& pFieldItem = 
				CCollisionMgr::Collision_Obj(
				CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER),
				CObjMgr::Get_Instance()->Get_TypeObj(OBJ_FIELDITEM));
			
			// 인벤토리 데이터로 복사하여
			CObj& pInventoryItem = pFieldItem; // 별명

			// 인벤토리 데이터에 추가하고
			pInventory.push_back(pInventoryItem);

			// 주운 아이템은 씬에서 삭제한다
			pFieldItem.Set_Dead();
		}
	}

#pragma endregion

#pragma region 인벤토리

	else if (CKeyMgr::Get_Instance()->Key_IN('I'))
	{
		if (m_bInvenOpen == false)
		{
			if (m_dwOpen + 500 < GetTickCount())
			{
				CUiMgr::Get_Instance()->Add_Object(UI_INVEN, CAbstractFactoryUI<CInventoryUI>::Create());
				m_bInvenOpen = true;
				m_dwOpen = GetTickCount();
			}
		}
		else
		{
			if (m_dwOpen + 500 < GetTickCount())
			{
				CUiMgr::Get_Instance()->Get_TypeUI(UI_INVEN).front()->Remove_InventoryUI();
				m_bInvenOpen = false;
				m_dwOpen = GetTickCount();
			}
		}
	}

#pragma endregion

#pragma region 펫 생성

	else if (CKeyMgr::Get_Instance()->Key_IN('P'))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_PET, CAbstractFactory<CPinkFox>::Create(m_tInfo.fX, m_tInfo.fY));
		CObjMgr::Get_Instance()->Add_Object(OBJ_PET, CAbstractFactory<CYellowFox>::Create(m_tInfo.fX, m_tInfo.fY));
		CObjMgr::Get_Instance()->Add_Object(OBJ_PET, CAbstractFactory<CBlueFox>::Create(m_tInfo.fX, m_tInfo.fY));
	}

#pragma endregion

#pragma region 점프 (Space)

	else if (CKeyMgr::Get_Instance()->Key_ING(VK_LEFT))
	{
		if (CKeyMgr::Get_Instance()->Key_IN(VK_SPACE))
		{
			m_bJump = true;
			m_fAngle = 45.f;
			m_eCurState = ST_JUMP;
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
			m_eDir = DIR_LEFT;
			m_eCurState = ST_WALK1;
		}
	}

	else if (CKeyMgr::Get_Instance()->Key_ING(VK_RIGHT))
	{
		if (CKeyMgr::Get_Instance()->Key_IN(VK_SPACE))
		{
			m_bJump = true;
			m_fAngle = 45.f;
			m_eCurState = ST_JUMP;
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
			m_eDir = DIR_RIGHT;
			m_eCurState = ST_WALK1;
		}
	}

	else if (
		!CKeyMgr::Get_Instance()->Key_ING(VK_LEFT) &&
		!CKeyMgr::Get_Instance()->Key_ING(VK_RIGHT) &&		
		CKeyMgr::Get_Instance()->Key_IN(VK_SPACE)) // 수직 점프
	{
		m_bJump = true;
		m_fAngle = 90.f;
		m_eCurState = ST_JUMP;
	}

#pragma endregion

#pragma region 좌우이동

	else if (CKeyMgr::Get_Instance()->Key_ING(VK_DOWN) &&
		CKeyMgr::Get_Instance()->Key_ING(VK_LCONTROL) )
	{
		m_eCurState = ST_PRONESTAB;
	}
	else if (CKeyMgr::Get_Instance()->Key_ING(VK_DOWN))
	{
		m_eCurState = ST_PRONE;

	}
	else if (CKeyMgr::Get_Instance()->Key_IN(VK_LCONTROL))
	{
		m_eCurState = ST_STAB2;
	}
	else if (CKeyMgr::Get_Instance()->Key_IN('X'))
	{
		m_eCurState = ST_SIT;
	}
	else
	{
		if (m_bJump == false)
			m_eCurState = ST_STAND1;
	}

#pragma endregion
}

void CPlayer::Jump()
{
	float	fY(0.f);

	// 점프든 아니든 우선 플레이어의 X 좌표에 해당하는 선분의 Y 좌표를 가져온다
	bool	bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, m_tInfo.fY, &fY);

	// 점프일때는 포물선을 뛰지만
	if (m_bJump)
	{
		m_tInfo.fY -= m_fPower * sin(m_fAngle) * m_fTime - ((9.8f * m_fTime * m_fTime) * 0.5f);
		m_fTime += 0.2f; 

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}
	// 점프를 하지 않았어도 선 위에 서게 된다
	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}
}

void CPlayer::Offset()
{
	// 내가 이동한만큼 배경이 반대로 이동할 크기
	float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	// 배경 크기
	float	fBgWidth = CSceneMgr::Get_Instance()->Get_TotalWidth();
	float	fBgHeight = CSceneMgr::Get_Instance()->Get_TotalHeight();

	// 화면 중심
	float	fHalfWINCX = WINCX * 0.5;
	float	fHalfWINCY = WINCY * 0.5;

	// 배경 마진
	float	fLeftMargin = fHalfWINCX - m_tInfo.fCX * 0.5f;
	float	fRightMargin = fBgWidth - fLeftMargin;
	float	fTopMargin = fHalfWINCY /*- m_tInfo.fCY * 0.5f*/;
	float	fBottomMargin = fBgHeight - fTopMargin;

	// 스크롤 마진
	float	fMaxScrollX = 0.f;				 // 왼쪽끝
	float	fMinScrollX = WINCX - fBgWidth;	 // 오른쪽끝
	float	fMaxScrollY = 0.f;				 // 위쪽끝
	float	fMinScrollY = WINCY - fBgHeight; // 아래쪽끝

	if (m_tInfo.fX + fScrollX < fHalfWINCX) // 왼쪽으로 이동할때
	{
		if (m_tRect.left > fLeftMargin) // 왼쪽 마진 안에 있을때
			CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);
		else
			CScrollMgr::Get_Instance()->Set_ScrollX(0.f);
	}

	else if (m_tInfo.fX + fScrollX > fHalfWINCX) // 오른쪽으로 이동할때
	{
		if (m_tRect.right < fRightMargin) // 오른쪽 마진 안에 있을때
			CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);
		else
			CScrollMgr::Get_Instance()->Set_ScrollX(0.f);
	}

	if (m_tInfo.fY + fScrollY < fHalfWINCY) // 위쪽으로 이동할때
	{
		if (m_tRect.top > fTopMargin) // 위쪽 마진 안에 있을때
			CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);
		else
			CScrollMgr::Get_Instance()->Set_ScrollY(0.f);
	}

	else if (m_tInfo.fY + fScrollY > fHalfWINCY) // 아래쪽으로 이동할때
	{
		if (m_tRect.bottom < fBottomMargin) // 아래쪽 마진 안에 있을때
			CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
		else
			CScrollMgr::Get_Instance()->Set_ScrollY(0.f);
	}

}

void CPlayer::FrameKey_Change()
{
#pragma region 알파 모션

	if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STAND1 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_stand1_left_0121";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STAND1 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_stand1_right_0121";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_WALK1 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_walk1_left_0123";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_WALK1 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_walk1_right_0123";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_ROPE)
		m_pFrameKey = L"alpha_rope_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_LADDER)
		m_pFrameKey = L"alpha_ladder_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_PRONE && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_prone_left_0";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_PRONE && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_prone_right_0";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_PRONESTAB && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_proneStab_left_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_PRONESTAB && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_proneStab_right_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SIT && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_sit_left_0";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SIT && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_sit_right_0";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_JUMP && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_jump_left_0";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_JUMP && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_jump_right_0";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_HEAL && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_heal_left_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_HEAL && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_heal_right_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STAB1 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_stabO1_left_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STAB1 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_stabO1_right_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STAB2 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_stabO2_left_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STAB2 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_stabO2_right_01";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STABF && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_stabOF_left_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_STABF && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_stabOF_right_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWING1 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_swingT1_left_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWING1 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_swingT1_right_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWING2 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_swingT2_left_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWING2 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_swingT2_right_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWING3 && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_swingT3_left_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWING2 && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_swingT3_right_012";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWINGF && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_swingTF_left_0123";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_SWINGF && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_swingTF_right_0123";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_ALERT && m_eDir == DIR_LEFT)
		m_pFrameKey = L"alpha_alert_left_0121";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_ALERT && m_eDir == DIR_RIGHT)
		m_pFrameKey = L"alpha_alert_right_0121";

	else if (m_eCurZero == ZERO_ALPHA && m_eCurState == ST_DEAD)
		m_pFrameKey = L"alpha_dead_0";

#pragma endregion

#pragma region 베타 모션


	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STAND1 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_stand1_left_0121";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STAND1 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_stand1_right_0121";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_WALK1 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_walk1_left_0123";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_WALK1 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_walk1_right_0123";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_ROPE)
	m_pFrameKey = L"beta_rope_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_LADDER)
	m_pFrameKey = L"beta_ladder_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_PRONE && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_prone_left_0";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_PRONE && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_prone_right_0";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_PRONESTAB && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_proneStab_left_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_PRONESTAB && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_proneStab_right_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SIT && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_sit_left_0";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SIT && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_sit_right_0";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_JUMP && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_jump_left_0";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_JUMP && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_jump_right_0";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_HEAL && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_heal_left_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_HEAL && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_heal_right_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STAB1 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_stabO1_left_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STAB1 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_stabO1_right_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STAB2 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_stabO2_left_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STAB2 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_stabO2_right_01";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STABF && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_stabOF_left_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_STABF && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_stabOF_right_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWING1 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_swingT1_left_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWING1 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_swingT1_right_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWING2 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_swingT2_left_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWING2 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_swingT2_right_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWING3 && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_swingT3_left_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWING3 && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_swingT3_right_012";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWINGF && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_swingTF_left_0123";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_SWINGF && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_swingTF_right_0123";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_ALERT && m_eDir == DIR_LEFT)
	m_pFrameKey = L"beta_alert_left_0121";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_ALERT && m_eDir == DIR_RIGHT)
	m_pFrameKey = L"beta_alert_left_0121";

	else if (m_eCurZero == ZERO_BETA && m_eCurState == ST_DEAD)
	m_pFrameKey = L"beta_dead_0";

#pragma endregion

}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CPlayer::ST_STAND1:
			m_tFrame = { 0, 3, 0, 200, GetTickCount()};
			break;

		case CPlayer::ST_WALK1:
			m_tFrame = { 0, 3, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_ROPE:
			m_tFrame = { 0, 1, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_LADDER:
			m_tFrame = { 0, 1, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_PRONE:
			m_tFrame = { 0, 0, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_PRONESTAB:
			m_tFrame = { 0, 1, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_SIT:
			m_tFrame = { 0, 0, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_JUMP:
			m_tFrame = { 0, 0, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_HEAL:
			m_tFrame = { 0, 2, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_STAB1:
			m_tFrame = { 0, 1, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_STAB2:
			m_tFrame = { 0, 1, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_STABF:
			m_tFrame = { 0, 2, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_SWING1:
			m_tFrame = { 0, 2, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_SWING2:
			m_tFrame = { 0, 2, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_SWING3:
			m_tFrame = { 0, 2, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_SWINGF:
			m_tFrame = { 0, 3, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_ALERT:
			m_tFrame = { 0, 3, 0, 200, GetTickCount() };
			break;

		case CPlayer::ST_DEAD:
			m_tFrame = { 0, 0, 0, 200, GetTickCount() };
			break;

		}
		m_ePreState = m_eCurState;
	}
}

void CPlayer::Zero_Change()
{
	if (m_ePreZero != m_eCurZero)
	{
		// 어시스트 공격(생략)

		float fTempHp(0.f);
		fTempHp = m_fHp;
		m_fHp = m_fAssistHp;
		m_fAssistHp = fTempHp;

		float fTempTp(0.f);
		fTempTp = m_fTp;
		m_fTp = m_fAssistTp;
		m_fAssistTp = fTempTp;

		m_ePreZero = m_eCurZero;
	}
	else
	{
		if (m_dwTime + 100 < GetTickCount())
		{
			if (m_fAssistHp < m_fMaxHp)
				m_fAssistHp += 100.f;

			if (m_fAssistTp < m_fMaxTp)
				m_fAssistTp += 1.f;

			m_dwTime = GetTickCount();
		}
	}
}

void CPlayer::Skill_Alpha_moonStrike(DIRID eDir)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL, 
		CAbstractFactory<CSKill_moonStrike>::Create(m_tInfo.fX, m_tInfo.fY, m_eDir));
}

void CPlayer::Skill_Alpha_flashAssaulter(DIRID eDir)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL,
		CAbstractFactory<CSkill_flashAssaulter>::Create(m_tInfo.fX, m_tInfo.fY - 25.f, m_eDir));
}

void CPlayer::Skill_Beta_upperSlash(DIRID eDir)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL,
		CAbstractFactory<CSkill_upperSlash>::Create(m_tInfo.fX, m_tInfo.fY - 100.f, m_eDir));
}

void CPlayer::Skill_Beta_frontSlash(DIRID eDir)
{
	CObjMgr::Get_Instance()->Add_Object(OBJ_SKILL,
		CAbstractFactory<CSkill_frontSlash>::Create(m_tInfo.fX, m_tInfo.fY, m_eDir));
}

void CPlayer::Lose_HP()
{
	bool bMob = CCollisionMgr::CheckObj_Multi(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_BOSS));

	bool bMobSkill = CCollisionMgr::CheckObj_Multi(
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PLAYER),
		CObjMgr::Get_Instance()->Get_TypeObj(OBJ_BSKILL));

	if (bMob == true)
	{
		m_fHp -= 50.f;
	}

	if (bMobSkill == true)
	{
		m_fHp -= 50.f;
	}

	if (m_fHp < 0)
	{
		m_eCurState = ST_DEAD;
	}
}

void CPlayer::Collect_Item()
{
	// 주변에 아이템이 있으며		
	bool bItem =
		CCollisionMgr::CheckObj_Multi(
			CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PET),
			CObjMgr::Get_Instance()->Get_TypeObj(OBJ_FIELDITEM));

	list<CObj>& pInventory = CObj::Get_MyItemList();

	if (bItem == true &&
		pInventory.size() <= 24)
	{
		// 아이템 주워서
		CObj& pFieldItem = CCollisionMgr::Collision_Obj(
			CObjMgr::Get_Instance()->Get_TypeObj(OBJ_PET),
			CObjMgr::Get_Instance()->Get_TypeObj(OBJ_FIELDITEM));

		// 인벤토리 데이터로 복사하여
		CObj& pInventoryItem = pFieldItem; // 별명

		// 인벤토리 데이터에 추가하고
		pInventory.push_back(pInventoryItem);

		// 주운 아이템은 씬에서 삭제한다
		pFieldItem.Set_Dead();
	}


}

void CPlayer::Kill_Mob()
{
}
