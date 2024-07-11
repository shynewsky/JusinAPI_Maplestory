#pragma once

#include "Obj.h"

class CItem_OrangePotion : public CObj
{
public:
	CItem_OrangePotion();
	virtual ~CItem_OrangePotion();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
