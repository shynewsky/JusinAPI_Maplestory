#pragma once

#include "Obj.h"

class CBlueFox : public CObj
{
public:
	CBlueFox();
	virtual ~CBlueFox();

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
