#pragma once

#include "Obj.h"

class CNPC_Dello : public CObj
{
public:
	CNPC_Dello();
	virtual	~CNPC_Dello();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};

