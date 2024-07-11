#pragma once

#include "Obj.h"

class CSkill_flashAssaulter : public CObj
{
public:
	CSkill_flashAssaulter();
	virtual ~CSkill_flashAssaulter();

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
