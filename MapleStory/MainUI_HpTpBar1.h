#pragma once

#include "Ui.h"

class CMainUI_HpTpBar1 : public CUi
{
public:
	CMainUI_HpTpBar1();
	virtual ~CMainUI_HpTpBar1();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
