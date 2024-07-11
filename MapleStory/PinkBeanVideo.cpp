#include "pch.h"
#include "PinkBeanVideo.h"

#include "SceneMgr.h"

CPinkBeanVideo::CPinkBeanVideo()
{
}

CPinkBeanVideo::~CPinkBeanVideo()
{
	Release();
}

void CPinkBeanVideo::Initialize()
{
	// MCIWndCreate : 멀티미디어를 재생하기 위한 창을 생성하는 함수

	m_hVideo = MCIWndCreate(
		g_hWnd,										// 부모 창 핸들
		nullptr,									// mci 윈도우를 사용하는 인스턴스 핸들
		WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,	// 윈도우 모양 옵션(자식 창 | 그 즉시 재생 | 플레이 바를 생성하지 않음)
		L"../Data/Video/Pinkbean.wmv");				// 재생할 파일의 경로(파일 이름까지 포함)

	// MoveWindow : 동영상 재생 크기를 설정
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);

	MCIWndPlay(m_hVideo);
}

int CPinkBeanVideo::Update()
{
	return 0;
}

void CPinkBeanVideo::Late_Update()
{
	if (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo))
	{
		CSceneMgr::Get_Instance()->Set_PBVideo(true);
		CSceneMgr::Get_Instance()->Scene_Change(Scene7_GodsDusk);
		return;
	}
}

void CPinkBeanVideo::Render(HDC hDC)
{
}

void CPinkBeanVideo::Release()
{
	MCIWndClose(m_hVideo);
}
