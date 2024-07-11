#pragma once

#include "Ui.h"

class CMainUi_ExpGauge : public CUi
{
public:
	CMainUi_ExpGauge();
	virtual ~CMainUi_ExpGauge();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
