#pragma once

#include "Obj.h"

class CSKill_moonStrike : public CObj
{
public:
	CSKill_moonStrike();
	virtual ~CSKill_moonStrike();

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
