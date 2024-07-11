#pragma once

#include "Obj.h"

class CBoss_MiddleGirl : public CObj
{
public:
	CBoss_MiddleGirl();
	virtual	~CBoss_MiddleGirl();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

private:
	// 크기 370 * 370
	float	m_fNpcWidth;
	float	m_fNpcHeight;

	// 발판좌표 (905,300)
	float	m_fNpcFootX;
	float	m_fNpcFootY;
};
