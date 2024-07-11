#pragma once

#include "MyBmp.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	static CBmpMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;

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
	static CBmpMgr* m_pInstance;

	//--------------------------------------------------------------------//

private:
	map<const TCHAR*, CMyBmp*> m_mapBit;

public:
	void		Add_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC			Find_Bmp(const TCHAR* pImgKey);
	void		Release();

};