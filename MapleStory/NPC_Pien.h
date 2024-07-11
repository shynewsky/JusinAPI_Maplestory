#pragma once

#include "Obj.h"

class CNPC_Pien : public CObj
{
public:
	CNPC_Pien();
	virtual	~CNPC_Pien();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

};

