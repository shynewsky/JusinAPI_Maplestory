#pragma once

#include "Obj.h"

class CNPC_Kirstern : public CObj
{
public:
	CNPC_Kirstern();
	virtual	~CNPC_Kirstern();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};

