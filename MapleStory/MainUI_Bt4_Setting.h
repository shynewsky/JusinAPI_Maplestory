#pragma once

#include "UI.h"

class CMainUI_Bt4_Setting : public CUi
{
public:
	CMainUI_Bt4_Setting();
	~CMainUI_Bt4_Setting();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID = 0;
};