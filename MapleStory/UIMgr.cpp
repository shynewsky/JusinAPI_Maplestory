#include "pch.h"
#include "UiMgr.h"

#include "CollisionMgr.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;

CUiMgr::CUiMgr()
{
}

CUiMgr::~CUiMgr()
{
	Release();
}


void CUiMgr::Add_Object(UIID eID, CUi* pUI)
{
	if (UI_END <= eID || nullptr == pUI)
		return;

	m_UiList[eID].push_back(pUI);
}

void CUiMgr::Update()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto iter = m_UiList[i].begin();
			iter != m_UiList[i].end(); )
		{
			int	iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CUi*>(*iter);
				iter = m_UiList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CUiMgr::Late_Update()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UiList[i])
		{
			iter->Late_Update();

			if (m_UiList[i].empty())
				break;
		}
	}
}

void CUiMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter : m_UiList[i])
		{
			iter->Render(hDC);

			if (m_UiList[i].empty())
				break;
		}
	}
}

void CUiMgr::Release()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for_each(m_UiList[i].begin(), m_UiList[i].end(), Safe_Delete<CUi*>);
		m_UiList[i].clear();
	}
}