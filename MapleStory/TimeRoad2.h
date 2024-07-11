#pragma once

#include "Scene.h"

class CTimeRoad2 : public CScene
{
public:
	CTimeRoad2();
	virtual ~CTimeRoad2();

public:
	virtual void Initialize()	override;
	virtual int	 Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

};

