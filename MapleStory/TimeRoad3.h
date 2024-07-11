#pragma once

#include "Scene.h"

class CTimeRoad3 : public CScene
{
public:
	CTimeRoad3();
	virtual ~CTimeRoad3();

public:
	virtual void Initialize()	override;
	virtual int	 Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

};

