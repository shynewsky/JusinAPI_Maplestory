#pragma once

#include "Obj.h"

class CNPC_Cell : public CObj
{
public:
	CNPC_Cell();
	virtual	~CNPC_Cell();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
