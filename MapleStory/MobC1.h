#pragma once

#include "Obj.h"

class CMobC1 : public CObj
{
public:
	CMobC1();
	virtual	~CMobC1();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	//---------------------------------------------------

private:
	enum STATE { STAND, HIT, DIE, END };

	STATE		m_ePreState;
	STATE		m_eCurState;
	DWORD		m_dwTime;
	bool		m_bItemDrop;

	void		Motion_Change();

};
