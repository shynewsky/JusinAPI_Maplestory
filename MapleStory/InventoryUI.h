#pragma once

#include "Ui.h"

class CInventoryUI : public CUi
{
public:
	CInventoryUI();
	virtual ~CInventoryUI();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	//-----------------------------------------------------

private:
	int			m_iPreItemCount;
	int			m_iCurItemCount;

private:
	void		Set_ItemSlot();
	TCHAR*		Find_FrameKey(ITEMNAME eID);

	//-----------------------------------------------------

private:
	int				m_iStartSlot;
	int				m_iEndSlot;

private:
	void			Check_Click();

	//-----------------------------------------------------
};