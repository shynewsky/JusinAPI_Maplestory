#pragma once

#include "Ui.h"

class CMainUI_AssistHp : public CUi
{
public:
	CMainUI_AssistHp();
	virtual ~CMainUI_AssistHp();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
