#pragma once

#include "Obj.h"

class CItem_BluePotion : public CObj
{
public:
	CItem_BluePotion();
	virtual ~CItem_BluePotion();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
