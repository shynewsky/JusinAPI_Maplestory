#pragma once

#include "Ui.h"

class CMainUI_ExpBar : public CUi
{
public:
	CMainUI_ExpBar();
	virtual ~CMainUI_ExpBar();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
