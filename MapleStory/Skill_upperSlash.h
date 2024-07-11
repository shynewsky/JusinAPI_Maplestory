#pragma once

#include "Obj.h"

class CSkill_upperSlash : public CObj
{
public:
	CSkill_upperSlash();
	virtual ~CSkill_upperSlash();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	//-----------------------------------

private:
	DWORD m_dwTime;

};

