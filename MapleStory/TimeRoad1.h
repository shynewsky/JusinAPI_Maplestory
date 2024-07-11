#pragma once

#include "Scene.h"

class CTimeRoad1 : public CScene
{
public:
	CTimeRoad1();
	virtual ~CTimeRoad1();

public:
	virtual void Initialize()	override;
	virtual int	 Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

};

