#pragma once

#include "Obj.h"

class CPB_Genesis : public CObj
{
public:
	CPB_Genesis();
	virtual ~CPB_Genesis();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD	m_dwTime;
};

