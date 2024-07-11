#pragma once

#include "Ui.h"

class CMainUI_HpTpBar2 : public CUi
{
public:
	CMainUI_HpTpBar2();
	virtual ~CMainUI_HpTpBar2();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
