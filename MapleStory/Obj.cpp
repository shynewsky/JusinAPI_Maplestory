#include "pch.h"
#include "Obj.h"

//list<CObj*> CObj::MyItemList;
list<CObj> CObj::MyItemList;

CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f)
	, m_fRectCX(0.f), m_fRectCY(0.f), m_fBltCX(0.f), m_fBltCY(0.f), m_fBltX(0.f), m_fBltY(0.f), m_fFootHeight(0.f)
	, m_fExp(0.f), m_fMaxExp(0.f), m_fHp(0.f), m_fMaxHp(0.f), m_fTp(0.f), m_fMaxTp(0.f), m_fPower(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	//m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.top = long(m_tInfo.fY - m_tInfo.fCY);
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	//m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY);
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}