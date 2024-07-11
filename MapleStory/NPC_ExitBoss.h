#pragma once

#include "Obj.h"

class CNPC_ExitBoss : public CObj
{
public:
	CNPC_ExitBoss();
	virtual	~CNPC_ExitBoss();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

};
