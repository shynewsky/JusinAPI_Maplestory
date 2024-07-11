#pragma once

#include "Obj.h"

class CPortal2 : public CObj
{
public:
	CPortal2();
	virtual	~CPortal2();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
