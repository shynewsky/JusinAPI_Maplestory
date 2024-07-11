#pragma once

#include "Obj.h"

class CNPC_EnterBoss : public CObj
{
public:
	CNPC_EnterBoss();
	virtual	~CNPC_EnterBoss();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

};
