#pragma once

#include "Obj.h"

class CItem_Pinkbean_mark : public CObj
{
public:
	CItem_Pinkbean_mark();
	virtual ~CItem_Pinkbean_mark();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
