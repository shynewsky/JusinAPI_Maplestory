#pragma once
#include "Define.h"

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;

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
	static CKeyMgr* m_pInstance;

	//--------------------------------------------------------------------//

public:
	bool	Key_ING(int _iKey);
	bool	Key_IN(int _iKey);
	bool	Key_OUT(int _iKey);	

public:
	void	Update() {}

private:
	bool	m_bKeyState[VK_MAX];

};