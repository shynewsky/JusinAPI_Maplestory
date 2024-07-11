#pragma once

#include "UI.h"

class CMainUI_Bt0_Cash : public CUi
{
public:
	CMainUI_Bt0_Cash();
	~CMainUI_Bt0_Cash();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID = 0;

};

