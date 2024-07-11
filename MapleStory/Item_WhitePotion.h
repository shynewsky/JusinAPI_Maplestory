#pragma once

#include "Obj.h"

class CItem_WhitePotion : public CObj
{
public:
	CItem_WhitePotion();
	virtual ~CItem_WhitePotion();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
