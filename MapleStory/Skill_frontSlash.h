#pragma once

#include "Obj.h"

class CSkill_frontSlash : public CObj
{
public:
	CSkill_frontSlash();
	virtual ~CSkill_frontSlash();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD	m_dwTime;
};

