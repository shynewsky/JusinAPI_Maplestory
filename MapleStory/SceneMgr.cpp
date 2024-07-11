#include "pch.h"
#include "SceneMgr.h"

#include "KeyMgr.h"

#include "ZeroTemple.h"
#include "ThreeDoors.h"
#include "ForgottenDusk.h"
#include "GodsDusk.h"
#include "PinkBeanVideo.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_ePreScene(SC_END), m_eCurScene(Scene0_ZeroTemple)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case Scene0_ZeroTemple:
			m_pScene = new CZeroTemple;
			break;

		case Scene2_ThreeDoors:
			m_pScene = new CThreeDoors;
			break;

		case Scene6_ForgottenDusk:
			m_pScene = new CForgottenDusk;
			break;

		case Scene7_GodsDusk:
			m_pScene = new CGodsDusk;
			break;

		case Scene8_PinkbeanVideo:
			m_pScene = new CPinkBeanVideo;
			break;

		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
#pragma region 키입력으로 장면전환 (임시) --> 무슨 이유에서인지 지우면 스페이스바 클릭이 안된다

	if (CKeyMgr::Get_Instance()->Key_IN('1'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(Scene0_ZeroTemple);
		return;
	}

	//if (CKeyMgr::Get_Instance()->Key_IN('2'))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(Scene1_DimensionPath);
	//	return;
	//}

	if (CKeyMgr::Get_Instance()->Key_IN('2'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(Scene2_ThreeDoors);
		return;
	}

	//if (CKeyMgr::Get_Instance()->Key_IN('4'))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(Scene3_TimeRoad1);
	//	return;
	//}

	//if (CKeyMgr::Get_Instance()->Key_IN('5'))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(Scene4_TimeRoad2);
	//	return;
	//}

	//if (CKeyMgr::Get_Instance()->Key_IN('6'))
	//{
	//	CSceneMgr::Get_Instance()->Scene_Change(Scene5_TimeRoad3);
	//	return;
	//}

	if (CKeyMgr::Get_Instance()->Key_IN('3'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(Scene6_ForgottenDusk);
		return;
	}

	if (CKeyMgr::Get_Instance()->Key_IN('4'))
	{
		CSceneMgr::Get_Instance()->Scene_Change(Scene7_GodsDusk);
		return;
	}

#pragma endregion

	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
