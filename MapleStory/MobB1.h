#pragma once

#include "Obj.h"

class CMobB1 : public CObj
{
public:
	CMobB1();
	virtual	~CMobB1();

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
