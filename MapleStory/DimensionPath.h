#pragma once

#include "Scene.h"

class CDimensionPath : public CScene
{
public:
	CDimensionPath();
	virtual ~CDimensionPath();

public:
	virtual void Initialize()	override;
	virtual int	 Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;
};

