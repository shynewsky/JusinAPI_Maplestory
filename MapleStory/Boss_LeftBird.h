#pragma once

#include "Obj.h"

class CBoss_LeftBird : public CObj
{
public:
	CBoss_LeftBird();
	virtual	~CBoss_LeftBird();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

private:
	// 크기 440 * 590
	float	m_fNpcWidth;
	float	m_fNpcHeight;

	// 발판좌표 (591,585)
	float	m_fNpcFootX;
	float	m_fNpcFootY;
};
