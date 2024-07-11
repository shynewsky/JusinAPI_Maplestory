#pragma once

#include "Obj.h"

class CItem_Blackbean_Mark : public CObj
{
public:
	CItem_Blackbean_Mark();
	virtual ~CItem_Blackbean_Mark();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
