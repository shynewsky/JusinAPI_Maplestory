#pragma once

#include "UI.h"

class CBossUI_Bt2_Refuse : public CUi
{
public:
	CBossUI_Bt2_Refuse();
	~CBossUI_Bt2_Refuse();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	int		m_iDrawID = 0;
};