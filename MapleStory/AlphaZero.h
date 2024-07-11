#pragma once
#include "Obj.h"

class CBetaZero;

class CAlphaZero : public CObj
{
public:
	CAlphaZero();
	virtual ~CAlphaZero();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};

