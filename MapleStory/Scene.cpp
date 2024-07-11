#include "pch.h"
#include "Scene.h"

#include "ObjMgr.h"
#include "UiMgr.h"
#include "LineMgr.h"

CScene::CScene()
	: iTotalWidth(0), iTotalHeight(0)
{
}

CScene::~CScene()
{
}

void CScene::Remove_All()
{
	CLineMgr::Get_Instance()->Release();

#pragma region NPC 동시 삭제

	list<CObj*>& NpcList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_NPC);

	for (auto& Npc : NpcList)
	{
		Safe_Delete<CObj*>(Npc);
	}
	NpcList.clear();

#pragma endregion

#pragma region 보스, 보스스킬 삭제

	list<CObj*>& BossList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BOSS);
	list<CObj*>& BSkillList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_BSKILL);

	for (auto& Boss : BossList)
	{
		Safe_Delete<CObj*>(Boss);
	}
	BossList.clear();

	for (auto& BossSkill : BSkillList)
	{
		Safe_Delete<CObj*>(BossSkill);
	}
	BSkillList.clear();

#pragma endregion

#pragma region 포탈 동시 삭제

	list<CObj*>& PortalList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_PORTAL);

	for (auto& Protal : PortalList)
	{
		Safe_Delete<CObj*>(Protal);
	}
	PortalList.clear();

#pragma endregion

#pragma region 플레이어 스킬 삭제

	list<CObj*>& SkillList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_SKILL);

	for (auto& Skill : SkillList)
	{
		Safe_Delete<CObj*>(Skill);
	}
	SkillList.clear();

#pragma endregion

#pragma region 아이템 동시 삭제

	list<CObj*>& ItemList = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_FIELDITEM);

	for (auto& Item : ItemList)
	{
		Safe_Delete<CObj*>(Item);
	}
	ItemList.clear();

#pragma endregion

#pragma region 몹 개별 삭제

	list<CObj*>& MobA1List = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MOB_A1);
	list<CObj*>& MobB1List = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MOB_B1);
	list<CObj*>& MobC1List = CObjMgr::Get_Instance()->Get_TypeObj(OBJID::OBJ_MOB_C1);

	for (auto& Mob : MobA1List)
	{
		Safe_Delete<CObj*>(Mob);
	}
	MobA1List.clear();

	for (auto& Mob : MobB1List)
	{
		Safe_Delete<CObj*>(Mob);
	}
	MobB1List.clear();

	for (auto& Mob : MobC1List)
	{
		Safe_Delete<CObj*>(Mob);
	}
	MobC1List.clear();


#pragma endregion

#pragma region UI 삭제

	list<CUi*>& BossUIList = CUiMgr::Get_Instance()->Get_TypeUI(UIID::UI_BOSS);

	for (auto& BossUI : BossUIList)
	{
		Safe_Delete<CUi*>(BossUI);
	}
	BossUIList.clear();

#pragma endregion

	CLineMgr::Get_Instance()->Release();
}

void CScene::Remain_Some()
{
}

