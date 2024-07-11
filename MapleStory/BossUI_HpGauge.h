#pragma once

#include "Ui.h"

class CBossUI_HpGauge : public CUi
{
public:
	CBossUI_HpGauge();
	virtual ~CBossUI_HpGauge();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
