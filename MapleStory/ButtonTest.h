#pragma once

#include "UI.h"

class CButtonTest : public CUi
{
public:
	CButtonTest();
	~CButtonTest();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID = 0;



};