#pragma once

#include "Ui.h"

class CBossUI_HpBar : public CUi
{
public:
	CBossUI_HpBar();
	virtual ~CBossUI_HpBar();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
