#pragma once

#include "Obj.h"

class CYellowFox : public CObj
{
public:
	CYellowFox();
	virtual ~CYellowFox();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD	m_dwTime;

private:
	void	Move_Around();

};
