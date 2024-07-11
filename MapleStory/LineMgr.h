#pragma once

#include "Line.h"
#include "Obj.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;

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
	static CLineMgr* m_pInstance;

	//--------------------------------------------------------------------//

private:
	list<CLine*> m_LineList;

public:
	void		Initialize(SCENEID _eID);
	int			Update();
	void		Render(HDC hDC);
	void		Release();
	void		Load_Line(SCENEID _eID); // --> 열거체로 분기문을 만들어 %s로 경로를 작성하고, 로드한다?

public:
	bool		Collision_Line(float& fX, float& fY, float* pY);
};