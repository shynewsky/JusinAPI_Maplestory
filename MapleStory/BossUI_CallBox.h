#pragma once

#include "Ui.h"

class CBossUI_CallBox : public CUi
{
public:
	CBossUI_CallBox();
	virtual ~CBossUI_CallBox();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
