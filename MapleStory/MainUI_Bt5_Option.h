#pragma once

#include "UI.h"

class CMainUI_Bt5_Option : public CUi
{
public:
	CMainUI_Bt5_Option();
	~CMainUI_Bt5_Option();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID = 0;
};