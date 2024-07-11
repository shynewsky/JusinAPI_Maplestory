#pragma once

#include "Ui.h"

class CBossUI_EnterBox : public CUi
{
public:
	CBossUI_EnterBox();
	virtual ~CBossUI_EnterBox();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
