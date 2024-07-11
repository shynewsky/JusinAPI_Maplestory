#pragma once

#include "UI.h"

class CBossUI_Bt1_Accept : public CUi
{
public:
	CBossUI_Bt1_Accept();
	~CBossUI_Bt1_Accept();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID = 0;
};