#pragma once

#include "Define.h"
#include "Scene.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}
	static void		Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr* m_pInstance;

	//--------------------------------------------------------------------//

private:
	CScene*		m_pScene;

	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;

public:
	void		Scene_Change(SCENEID eID);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	//--------------------------------------------------------------------//

	// 플레이어에게 넘겨서 --> 스크롤 제한걸기

public:
	int		Get_TotalWidth() 
	{ 
		return m_pScene->Get_TotalWidth(); 
	}
	int		Get_TotalHeight() 
	{ 
		return m_pScene->Get_TotalHeight(); 
	}

	//--------------------------------------------------------------------//

public:
	SCENEID			Get_Scene() { return m_eCurScene; }

	//--------------------------------------------------------------------//

private:
	bool	m_bPBVideo = false;

public:
	void	Set_PBVideo(bool _b) { m_bPBVideo = _b; }
	bool	Get_PBVideo() { return m_bPBVideo; }
};
