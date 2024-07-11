#pragma once

#include "Obj.h"

class CBoss_LeftMan : public CObj
{
public:
	CBoss_LeftMan();
	virtual	~CBoss_LeftMan();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

private:
	// 크기 460 * 880
	float	m_fNpcWidth;
	float	m_fNpcHeight;

	// 발판좌표 (247,625)
	float	m_fNpcFootX;
	float	m_fNpcFootY;
};
