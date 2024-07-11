#pragma once

#include "Obj.h"

class CNPC_Ragun : public CObj
{
public:
	CNPC_Ragun();
	virtual	~CNPC_Ragun();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
