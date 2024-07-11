#pragma once

#include "Obj.h"

class CNPC_Chou : public CObj
{
public:
	CNPC_Chou();
	virtual	~CNPC_Chou();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
