#pragma once

#include "Obj.h"

class CItem_RedPotion : public CObj
{
public:
	CItem_RedPotion();
	virtual ~CItem_RedPotion();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
