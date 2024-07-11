#pragma once

#include "Scene.h"

class CPinkBeanVideo : public CScene
{
public:
	CPinkBeanVideo();
	virtual ~CPinkBeanVideo();

public:
	virtual void Initialize()	override;
	virtual int Update()		override;
	virtual void Late_Update()	override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

private:
	HWND		m_hVideo;
};

