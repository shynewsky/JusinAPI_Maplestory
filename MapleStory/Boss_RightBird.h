#pragma once

#include "Obj.h"

class CBoss_RightBird : public CObj
{
public:
	CBoss_RightBird();
	virtual	~CBoss_RightBird();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

private:
	// 크기 445 * 590
	float	m_fNpcWidth;
	float	m_fNpcHeight;

	// 발판좌표 (1212,585)
	float	m_fNpcFootX;
	float	m_fNpcFootY;
};
