#pragma once

#include "Ui.h"

class CUiTest : public CUi
{
public:
	CUiTest();
	virtual ~CUiTest();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
