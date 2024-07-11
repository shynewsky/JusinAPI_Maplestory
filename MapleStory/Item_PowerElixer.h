#pragma once

#include "Obj.h"

class CItem_PowerElixer : public CObj
{
public:
	CItem_PowerElixer();
	virtual ~CItem_PowerElixer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
