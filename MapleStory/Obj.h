#pragma once
#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void	Initialize() {}/*PURE;*/
	virtual int		Update() { return 0; }/*PURE;*/
	virtual void	Late_Update() {}/*PURE;*/
	virtual void	Render(HDC hDC) {}/*PURE;*/
	virtual void	Release() {}/*PURE;*/

	//--------------------------------------------------------------------//

protected:
	INFO	m_tInfo; // 중점좌표, 한변의길이
	RECT	m_tRect; // 각변의 좌표, 콜라이더(히트박스)
	float	m_fSpeed;

protected:
	float	m_fRectCX;	// 히트박스 가로세로
	float	m_fRectCY;

	float	m_fBltCX;	// 애니메이션 가로세로
	float	m_fBltCY;

	float	m_fBltX;	// 애니메이션 좌상단 시작점
	float	m_fBltY;

	float	m_fFootHeight; // 애니메이션에서 발바닥 공중부양 위치

protected:
	void	Update_Rect();

public:
	INFO	Get_Info() { return m_tInfo; }
	RECT&	Get_Rect() { return m_tRect; }
	void	Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }

	//--------------------------------------------------------------------//

protected:
	bool	m_bDead; // 충돌 후 삭제

public:
	bool	Get_Dead() { return m_bDead; }
	void	Set_Dead() { m_bDead = true; }

	//--------------------------------------------------------------------//

protected:
	FRAME			m_tFrame;			// 어디부터 어디까지 어떤 속도로 넘어가는지를 담은 구조체 자료형
	const TCHAR*	m_pFrameKey = L"";	// 어떤 이미지를 꺼내와야 할지 넣는 키 값
	bool			m_bTemp;

protected:
	void	Move_Frame();		// FRAME 구조체에 담긴 값으로 애니메이션화 하는 함수

public:
	void			Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }
	const TCHAR*	Get_FrameKey() { return m_pFrameKey; }

	//--------------------------------------------------------------------//

protected:
	DIRID	m_eDir;

public:
	void	Set_Dir(DIRID eDir) { m_eDir = eDir; }
	DIRID	Get_Dir() { return m_eDir; }

	//--------------------------------------------------------------------//

protected:
	float	m_fAngle; // 점프, 공격 각도

public:
	void	Set_Angle(float _fAngle) { m_fAngle = _fAngle; }

	//--------------------------------------------------------------------//

protected:
	float	m_fExp;
	float	m_fMaxExp;

	float	m_fHp;
	float	m_fMaxHp;

	float	m_fTp;
	float	m_fMaxTp;

	float	m_fPower;

public:
	float	Get_Exp() { return m_fExp; }
	float	Get_MaxExp() { return m_fMaxExp; }

	void	Set_Hp(float _fDamage) { m_fHp += _fDamage; }
	float	Get_Hp() { return m_fHp; }
	float	Get_MaxHp() { return m_fMaxHp; }

	float	Get_Tp() { return m_fTp; }
	float	Get_MaxTp() { return m_fMaxTp; }
	
	//--------------------------------------------------------------------//
	
protected:
	ITEMNAME	m_eItemName;
	ITEMTYPE	m_eItemType;

public:
	ITEMNAME	Get_ItemName() { return m_eItemName; }
	ITEMTYPE	Get_ItemType() { return m_eItemType; }
	
private:
	static	list<CObj> MyItemList;

public:
	list<CObj>&	Get_MyItemList() { return MyItemList; }

};


