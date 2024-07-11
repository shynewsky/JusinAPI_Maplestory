#pragma once
#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

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
	static CObjMgr* m_pInstance;

	//--------------------------------------------------------------------//

private:
	list<CObj*>	m_ObjList[OBJ_END];

public:
	void	Add_Object(OBJID eID, CObj* pObj);	// 다른 클래스에서 싱글톤으로 호출하여, 원하는 OBJID에 객체 추가
	void	Update();							// 반복자패턴으로 ObjList 요소 모두 Update()
	void	Late_Update();						// 반복자패턴으로 ObjList 요소 모두 Late_Update()
	void	Render(HDC hDC);					// 반복자패턴으로 ObjList 요소 모두 Render();
	void	Release();							// 반복자패턴으로 ObjList 요소 모두 Safe_Delete()

public:
	CObj* Get_Player() { return m_ObjList[OBJ_PLAYER].front(); }
	//CObj* Get_Target(OBJID eID, CObj* pObj);

	//--------------------------------------------------------------------//

public:
	list<CObj*>& Get_TypeObj(OBJID _e) { return m_ObjList[_e]; } // 맵 나갈때 특정 오브젝트 삭제용
};

