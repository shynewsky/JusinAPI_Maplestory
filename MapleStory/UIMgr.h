#pragma once
#include "Ui.h"

class CUiMgr
{
private:
	CUiMgr();
	~CUiMgr();

public:
	static CUiMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUiMgr;

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
	static CUiMgr* m_pInstance;

	//--------------------------------------------------------------------//

private:
	list<CUi*>	m_UiList[UI_END];

public:
	void	Add_Object(UIID eID, CUi* pObj);	// 다른 클래스에서 싱글톤으로 호출하여, 원하는 OBJID에 객체 추가
	void	Update();							// 반복자패턴으로 ObjList 요소 모두 Update()
	void	Late_Update();						// 반복자패턴으로 ObjList 요소 모두 Late_Update()
	void	Render(HDC hDC);					// 반복자패턴으로 ObjList 요소 모두 Render();
	void	Release();							// 반복자패턴으로 ObjList 요소 모두 Safe_Delete()

	//--------------------------------------------------------------------//

public:
	list<CUi*>& Get_TypeUI(UIID _e) { return m_UiList[_e]; } // 맵 나갈때 특정 오브젝트 삭제용


};

