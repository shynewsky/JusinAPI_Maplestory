#pragma once

#include "Obj.h"

class CBoss_Pinkbean : public CObj
{
public:
	CBoss_Pinkbean();
	virtual	~CBoss_Pinkbean();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	//---------------------------------------------------

private:
	enum PBSTATE 
	{
		PB_STAND, PB_HIT, PB_DIE, PB_DEAD,
		PB_GENESIS, PB_MUSICNOTE, PB_RETURNATTACK,
		PB_END 
	};

	PBSTATE		m_ePrePB;
	PBSTATE		m_eCurPB;
	DWORD		m_dwTime;

	bool		m_bMusicNote; // 애니메이션이 끝났는지
	bool		m_bGenesis;
	bool		m_bItemDrop;

	void	Attack_Pattern();
	void	Motion_Change();

	void	Skill_Genesis();
	void	Skill_MusicNote();
	void	Skill_ReturnAttack();



};
