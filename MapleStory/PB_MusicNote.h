#pragma once

#include "Obj.h"

class CPB_MusicNote : public CObj
{
public:
	CPB_MusicNote();
	virtual ~CPB_MusicNote();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	DWORD	m_dwTime;
};

