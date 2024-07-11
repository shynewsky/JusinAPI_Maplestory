#pragma once

#include "Ui.h"

class CBossUI_ExitBox : public CUi
{
public:
	CBossUI_ExitBox();
	virtual ~CBossUI_ExitBox();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
