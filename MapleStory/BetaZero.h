#pragma once

#include "Player.h"

class CAlphaZero;

class CBetaZero : public CPlayer
{
public:
	CBetaZero();
	virtual ~CBetaZero();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;
};
