#pragma once

#include "Ui.h"

class CMainUI_AssistTp : public CUi
{
public:
	CMainUI_AssistTp();
	virtual ~CMainUI_AssistTp();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
