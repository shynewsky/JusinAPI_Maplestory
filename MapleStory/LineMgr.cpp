#include "pch.h"
#include "LineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize(SCENEID _eID)
{
	Load_Line(_eID);
}

int CLineMgr::Update()
{
	return 0;
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

void CLineMgr::Load_Line(SCENEID _eID)
{
	HANDLE hFile = nullptr;

	switch (_eID)
	{
	case Scene0_ZeroTemple:
		hFile = CreateFile(L"../Data/Line/Line0_ZeroTemple.dat", GENERIC_READ,
			NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;

	case Scene2_ThreeDoors:
		hFile = CreateFile(L"../Data/Line/Line2_ThreeDoors.dat", GENERIC_READ,
			NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;

	case Scene6_ForgottenDusk:
		hFile = CreateFile(L"../Data/Line/Line6_ForgottenDusk.dat", GENERIC_READ,
			NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;

	case Scene7_GodsDusk:
		hFile = CreateFile(L"../Data/Line/Line7_GodsDusk.dat", GENERIC_READ,
			NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;
	}

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);	// 예외 처리 변수
	LINE	tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINE), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);
}

bool CLineMgr::Collision_Line(float& fX, float& fY, float* pY) // 걷기만 가능
{
	if (m_LineList.empty())
		return false;

	CLine* pTargetLine = nullptr;

	float fDistance = 0.f;

	for (auto& iter : m_LineList)
	{
		// 1) X 범위에 플레이어가 들어오는 선분을 고른다

		if (fX >= iter->Get_Info().tLPoint.fX &&
			fX <= iter->Get_Info().tRPoint.fX)
		{

			// 2) 플레이어의 Y 좌표보다 큰 선분들을 고른다

			// 직선의 방정식으로 선분을 만든다
			float x1 = iter->Get_Info().tLPoint.fX;
			float y1 = iter->Get_Info().tLPoint.fY;
			float x2 = iter->Get_Info().tRPoint.fX;
			float y2 = iter->Get_Info().tRPoint.fY;

			// 플레이어의 좌표를 대입하여 선분과의 거리를 구한다
			*pY  = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;
			float fDiagonal = abs(*pY - fY);

			if (*pY > fY) // 선분이 플레이어보다 아래에 있다
			{
				// 3) 플레이어와 가장 가까운 선분을 타겟선분으로 잡는다

				if (!pTargetLine // 최초일때 fDistance 는 처음 우한 거리로 넣고
					|| fDiagonal < fDistance) // 새로 구한 거리가 더 작은 경우
				{
					fDistance = fDiagonal;
					pTargetLine = iter;
				}
			}
		}
	}

	if (!pTargetLine)
		return false;

	float x1 = pTargetLine->Get_Info().tLPoint.fX;
	float y1 = pTargetLine->Get_Info().tLPoint.fY;
	float x2 = pTargetLine->Get_Info().tRPoint.fX;
	float y2 = pTargetLine->Get_Info().tRPoint.fY;

	*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

	return true;
}

#pragma region 선충돌 수정예정 - 점프, 벽충돌, 낙하

//bool CLineMgr::On_Line(CObj* _pObj)
//{
//	if (m_LineList.empty())
//		return false;
//
//	m_pTargetLine = nullptr;
//
//	float fDistance = 0.f;
//
//	for (auto& iter : m_LineList)
//	{
//		// * FLOOR, WALL, ROPE, LADDER 구분을 어떻게 하지?
//		//if (iter->Get_ID() != FLOOR)
//		//{
//		//	continue;
//		//}
//
//		// 1) X 범위에 플레이어가 들어오는 선분을 고른다
//
//		if (_pObj->Get_Info().fX >= iter->Get_Info().tLPoint.fX
//			&& _pObj->Get_Info().fX < iter->Get_Info().tRPoint.fX)
//		{
//
//			// 2) 플레이어의 Y 좌표보다 큰 선분들을 고른다
//
//			// 현재 플레이어의 중점 좌표
//			float a = _pObj->Get_Info().fX;
//			float b = _pObj->Get_Info().fY;
//
//			// 직선의 방정식으로 선분을 만든다
//			float x1 = iter->Get_Info().tLPoint.fX;
//			float y1 = iter->Get_Info().tLPoint.fY;
//			float x2 = iter->Get_Info().tRPoint.fX;
//			float y2 = iter->Get_Info().tRPoint.fY;
//
//			// 플레이어의 좌표를 대입하여 선분과의 거리를 구한다
//			float fLineY = ((y2 - y1) / (x2 - x1)) * (a - x1) + y1;
//			float fDiagonal = abs(fLineY - b);
//
//			if (fLineY > b) // 선분이 플레이어보다 아래에 있다
//			{
//				// 3) 플레이어와 가장 가까운 선분을 타겟선분으로 잡는다
//
//				if (!m_pTargetLine // 최초일때 fDistance 는 처음 우한 거리로 넣고
//					|| fDiagonal < fDistance) // 새로 구한 거리가 더 작은 경우
//				{
//					fDistance = fDiagonal;
//					m_pTargetLine = iter;
//				}
//			}
//
//			m_pTargetLine = iter;
//		}
//	}
//
//	if (!m_pTargetLine)
//		return false;
//
//	// 4) 타겟선분 위에 있는지 확인한다
//
//	float a = _pObj->Get_Info().fX;
//	float b = _pObj->Get_Info().fY;
//
//	float x1 = m_pTargetLine->Get_Info().tLPoint.fX;
//	float y1 = m_pTargetLine->Get_Info().tLPoint.fY;
//	float x2 = m_pTargetLine->Get_Info().tRPoint.fX;
//	float y2 = m_pTargetLine->Get_Info().tRPoint.fY;
//
//	float fLineY = ((y2 - y1) / (x2 - x1)) * (a - x1) + y1;
//
//	if (fLineY == b) // 플레이어가 선분위에 있을때 (걷기, 엎드리기)
//	{
//		// x = v * cos(fAngle) * t 만큼 이동
//	}
//	else // 플레이어가 선분위에 없을때 (점프, 낙하)
//	{
//		// x = v * cos(fAngle) * t 만큼 이동
//		// y = v * sin(fAngle) * t - 9.8 * t * t * 0.5; 만큼 이동
//	}
//
//	// 점프했다는 전제하에
//		// CPlayer::Jump()
//		// false가 반환되면 --> 포물선에 따라서 추락
//		// true가 반환되면 --> 포물선에 따라서 추락한 후 착지
//
//	// 점프하지 않았다면?
//	// SPACE를 눌러서 bJump = true가 되고 Jump()가 호출되는 것인데
//	// 모든 이동에서 On_Line() 인지 판단하고 한다면
//	// if(GetKey~ == RIGHT)
//	// {
//	//		if(On_Line())
//	//		{
//	//			x = v * cos * t
//	//		}
//	//		else
//	//		{
//	//			x = v * cos * t
//	//			y  = v * sin * t - 9.8 * t * t * 
//	//		}
//	// }
//	//  --> 이런식으로 하면 되지 않을까?
//	// 아니면 Move() 라는 함수를 만들어서 이걸 포함시키고
//	// Collision_Floor(), Collision_Wall(), Collision_Clime()를 Late_Update()에서 확인
//
//}

#pragma endregion


