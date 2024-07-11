#pragma once

#include "ItemDB.h"

template<typename T>
class CAbstractFactoryITEM
{
public:
	static CItemDB* Create()
	{
		CItemDB* pItemDB = new T;

		pItemDB->Initialize();
		return pItemDB;
	}

	static CItemDB* Create(ITEMNAME _eItemName, ITEMTYPE _eItemTyoe, TCHAR* pFrameKey)
	{
		CItemDB* pItemDB = new T;
		pItemDB->Set_ItemName(_eItemName);
		pItemDB->Set_ItemType(_eItemTyoe);
		pItemDB->Set_FrameKey(pFrameKey);

		pItemDB->Initialize();
		return pItemDB;
	}


public:
	CAbstractFactoryITEM() {}
	~CAbstractFactoryITEM() {}
};