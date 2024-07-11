#pragma once

#include "Obj.h"

class CItem_BlackMage_Badge : public CObj
{
public:
	CItem_BlackMage_Badge();
	virtual ~CItem_BlackMage_Badge();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
