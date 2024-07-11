#pragma once

#include "Ui.h"

class CMainUI_AssistBar : public CUi
{
public:
	CMainUI_AssistBar();
	virtual ~CMainUI_AssistBar();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
