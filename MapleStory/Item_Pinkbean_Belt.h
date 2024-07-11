#pragma once

#include "Obj.h"

class CItem_Pinkbean_Belt : public CObj
{
public:
	CItem_Pinkbean_Belt();
	virtual ~CItem_Pinkbean_Belt();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
