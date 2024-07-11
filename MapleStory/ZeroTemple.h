#pragma once

#include "Scene.h"

class CZeroTemple : public CScene
{
public:
	CZeroTemple();
	virtual ~CZeroTemple();

public:
	virtual void Initialize()	override;
	virtual int	 Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

};

