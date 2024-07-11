#pragma once

#include "Obj.h"

class CPortal : public CObj
{
public:
	CPortal();
	virtual	~CPortal();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
