#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual		void		Initialize()	PURE;
	virtual		int			Update()		PURE;
	virtual		void		Late_Update()	PURE;
	virtual		void		Render(HDC hDC)	PURE;
	virtual		void		Release()		PURE;

	//---------------------------------------------

	// 플레이어에게 넘겨서 --> 스크롤 제한걸기

protected:
	int		iTotalWidth; // 1366
	int		iTotalHeight; // 767

public:
	int		Get_TotalWidth() { return iTotalWidth; }
	int		Get_TotalHeight() { return iTotalHeight; }

	//---------------------------------------------

	// 씬 전환할때 전 씬에 있던 오브젝트 삭제

public:
	void	Remove_All();
	void	Remain_Some();
};
