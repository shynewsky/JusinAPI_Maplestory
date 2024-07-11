#pragma once

extern	HWND		g_hWnd;

#define			WINCX		800
#define			WINCY		600

#define			PURE		= 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

#define			PI			3.141592f

#define			VK_MAX		0xff

//#define		TILECX		64
//#define		TILECY		64

//#define		TILEX		30
//#define		TILEY		20

// 2) 오브젝트 매니저가 오브젝트를 구분하는 분류 (Render 순서 주의)
enum OBJID 
{ 
	OBJ_NPC, 
	OBJ_MOB_A1,OBJ_MOB_B1,OBJ_MOB_C1,
	OBJ_BOSS, OBJ_BSKILL,
	OBJ_PET,
	OBJ_PLAYER, OBJ_SKILL, 
	OBJ_FIELDITEM,
	OBJ_PORTAL,

	OBJ_END 
};

enum DIRID { DIR_LEFT, DIR_RIGHT, DIR_END }; // 스킬 방향

enum ZEROID { ZERO_ALPHA, ZERO_BETA, ZERO_END };

enum ITEMLIST { ILIST_GAMEITEM, ILIST_MYITEM, ILIST_END };

enum ITEMTYPE 
{ 
	ITYPE_EQUIP, 
	ITYPE_CONSUME, 
	ITYPE_EXTRA, 
	ITYPE_INSTALL, 
	ITYPE_CASH, 
	ITYPE_BEAUTY, 
	
	ITYPE_END 
};

enum ITEMNAME 
{ 
	INAME_PowerElixer, 
	INAME_RedPotion,
	INAME_BluePotion,
	INAME_OrangePotion,
	INAME_WhitePotion,

	INAME_PinkbeanHat,
	INAME_PinkbeanSuit,
	INAME_PinkbeanMark,
	INAME_BlackbeanMark,
	INAME_BlackMageBadge,

	INAME_PinkbeanBalloon,
	INAME_PinkbeanBelt,
	INAME_PinkbeanCotton,
	INAME_PinkbeanCup,
	INAME_PinkbeanMeat,

	INAME_PinkbeanPet,
	INAME_PinkbeanPotion,
	INAME_PinkbeanSoul,

	INAME_END 
};

// 3) 유아이 매니저가 유아이를 구분하는 분류
enum UIID 
{ 
	UI_MAIN, UI_MBUTTON,
	UI_BOSS, 
	UI_POPUP, UI_PBUTTON,
	UI_INVEN, UI_IBUTTON, UI_ISLOT,
	UI_MOUSE, 

	UI_END
};

// 4) 라인 매니저가 라인을 구분하는 분류 (줄과 사다리는 모션이 달라서 구분함)
enum LINEID {LINE_FLOOR, LINE_WALL, LINE_ROPE, LINE_LADDER, LINE_END};

// 8) 씬 매니저가 씬을 구분하는 분류
enum SCENEID
{
	Scene0_ZeroTemple,
	Scene1_DimensionPath,
	Scene2_ThreeDoors,
	Scene3_TimeRoad1,
	Scene4_TimeRoad2,
	Scene5_TimeRoad3,
	Scene6_ForgottenDusk,
	Scene7_GodsDusk,
	Scene8_PinkbeanVideo,

	SC_END 
};

// ?
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_EFFECT, RENDER_UI, RENDER_END };

// 사운드 매니저
enum CHANNELID { SOUND_EFFECT, SOUND_BGM, MAXCHANNEL };

typedef struct tagInfo
{
	float		fX; // 중점 좌표
	float		fY;

	float		fCX; // 가로세로 크기
	float		fCY;

}INFO;

// LINEMGR에게 --> 좌표 제공
typedef struct tagPoint
{
	float	fX;
	float	fY;

	tagPoint() { ZeroMemory(this, sizeof(tagPoint)); }
	tagPoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}

}LINEPOINT;

// LINE에게 --> 양끝점 제공
typedef struct tagLine
{
	LINEPOINT		tLPoint;
	LINEPOINT		tRPoint;
	LINEID			eLineType;	// 추가

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint)
		: tLPoint(_tLPoint), tRPoint(_tRPoint) {}
	tagLine(LINEPOINT& _tLPoint, LINEPOINT& _tRPoint, LINEID _eLineType) // 추가
		: tLPoint(_tLPoint), tRPoint(_tRPoint), eLineType(_eLineType) {} 

}LINE;

// BMPMGR에게 --> 이미지를 어떻게 잘라야하는지 정보 제공
typedef struct tagFrame
{
	int		iFrameStart;	// 몇 열부터
	int		iFrameEnd;		// 몇 열까지
	int		iMotion;		// 몇 행의
	DWORD	dwSpeed;		
	DWORD	dwTime;

}FRAME;


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

// OBJ인 TILE 삭제
struct DeleteObj
{
	template<typename T>
	void	operator()(T& Obj)
	{
		if (Obj)
		{
			delete Obj;
			Obj = nullptr;
		}
	}
};

// MAP 컨테이너인 BMP 삭제
struct DeleteMap
{
	template<typename T>
	void	operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

// BMP의 맵 컨테이너에서 키 검색 (키가 같은 것을 찾는다)
class CStringCmp
{

public:
	CStringCmp(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(m_pString, MyPair.first);
	}

private:
	const	TCHAR* m_pString;
};

// ITEM의 맵 컨테이너에서 키 검색 (키가 같은 것을 찾는다)
class CItemNameCmp
{

public:
	CItemNameCmp(ITEMNAME eID) : m_eItemName(INAME_END) {}

public:
	template<typename T>
	bool operator()(T& MyPair)
	{
		return !lstrcmp(m_eItemName, MyPair.first);
	}

private:
	ITEMNAME m_eItemName;
};


