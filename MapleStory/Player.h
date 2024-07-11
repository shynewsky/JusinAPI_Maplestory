#pragma once

#include "Obj.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	Late_Update() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	//---------------------------------------------------

private:
	virtual void	Key_Input();

	//---------------------------------------------------

private:
	bool	m_bJump;
	float	m_fPower;
	float	m_fTime;

private:
	void	Jump();

	//---------------------------------------------------

private:
	void	Offset();

	//---------------------------------------------------

private:

	enum STATEID 
	{ 
		ST_STAND1, 
		ST_WALK1, // 좌우키
		ST_ROPE, ST_LADDER, // 상하키
		ST_PRONE, ST_PRONESTAB, // 아래키

		ST_SIT, // X 키
		ST_JUMP, // ALT 키
		ST_HEAL, // LShift 키

		// 일반공격 --> STAB2, SWING1, SWING3
		// 알파 문스트라이크 --> STABF
		// 알파 플래시어썰터 --> STABF
		// 베타 어퍼 슬래시 --> SWING3
		// 베타 프론트 슬래시 --> SWING3

		ST_STAB1, ST_STAB2, ST_STABF,
		ST_SWING1, ST_SWING2, ST_SWING3, ST_SWINGF,

		ST_ALERT, // 공격 이후
		ST_DEAD,  // 사망 시

		ST_END
	};

	STATEID	m_ePreState;
	STATEID	m_eCurState;

private:
	void	FrameKey_Change(); // STATEID에 따라 FrameKey 지정
	void	Motion_Change(); // FRAME m_tFrame의 변수값 변경

		//---------------------------------------------------

private:
	ZEROID	m_ePreZero;
	ZEROID	m_eCurZero;

private:
	void	Skill_Alpha_moonStrike(DIRID eDir);
	void	Skill_Alpha_flashAssaulter(DIRID eDir);
	void	Skill_Beta_upperSlash(DIRID eDir);
	void	Skill_Beta_frontSlash(DIRID eDir);

public:
	ZEROID	Get_CurZero() { return m_eCurZero; }

	//---------------------------------------------------
	
private:
	float	m_fAssistHp;
	float	m_fAssistTp;
	float	m_dwTime;

public:
	float	Get_AssistHp() { return m_fAssistHp; }
	float	Get_AssistTp() { return m_fAssistTp; }

private:
	void	Zero_Change();

	//---------------------------------------------------

private:
	void	Lose_HP();
	void	Collect_Item();
	void	Kill_Mob();

	//---------------------------------------------------

	// 개발자모드

private:
	DWORD	m_dwConsole;

	//---------------------------------------------------



private:
	bool	m_bInvenOpen;
	DWORD	m_dwOpen;
};
