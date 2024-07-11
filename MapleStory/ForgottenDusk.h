#pragma once

#include "Scene.h"

class CForgottenDusk : public CScene
{
public:
	CForgottenDusk();
	virtual ~CForgottenDusk();

public:
	virtual void Initialize()	override;
	virtual int	 Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

};

