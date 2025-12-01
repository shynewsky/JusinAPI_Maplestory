# WinAPI 메이플 모작 – JusinAPI_Maplestory

메이플스토리 리소스를 추출해 WinAPI 기반으로 제로/카오스 핑크빈 콘텐츠를 모작한 개인 프로젝트입니다.  
맵, 발판, 플레이어 이동·점프, 스크롤, 태그 시스템, 스킬, UI(게이지/인벤토리/버튼), 보스 패턴, 충돌 처리까지  
수업 코드 기반 엔진을 확장하면서 개발 과정을 정리한 문서를 기반으로 작성한 README입니다.

---

## 1. 리소스 추출 파이프라인

### 문제 상황
- 메이플스토리 WZ 포맷을 직접 파싱하기 어렵고, 상용 클라이언트를 그대로 사용할 수 없음.
- 배경·캐릭터·스킬·UI·사운드 리소스를 WinAPI에서 사용 가능한 BMP/PNG로 변환해야 했음.

### 해결 과정
- `WzComparerR2`(위컴알)로 `Base.wz` 파일을 열어 맵/아바타/기타 그래픽/사운드 등을 검색·미리 보기 후 개별 추출.
- 포토샵으로 리소스를 정리하고 (255, 0, 255) 배경을 깐 뒤 PNG로 저장 → 그림판에서 BMP로 변환.
- 아바타·NPC·UI·보스 이펙트는 투명도 문제를 해결하기 위해 여러 이미지를 겹쳐 100% 불투명한 스프라이트 시트를 제작.

### 결과
- 맵 8종, 제로/카핑/몬스터/NPC, 인벤토리·보스·퀘스트 UI 등 핵심 리소스를 `Data/` 폴더에 정리.
- 이후 모든 시스템(맵, 애니메이션, UI)에서 공통으로 활용 가능한 자산 세트 확보.

---

## 2. 씬 & 배경 렌더링

### 문제 상황
- WinAPI의 메시지 루프 위에 게임 루프(`Update → Late_Update → Render`)를 자연스럽게 얹어야 했음.

### 해결 과정

```cpp
while (true)
{
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (WM_QUIT == msg.message) break;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    else
    {
        if (dwTime + 10 < GetTickCount())
        {
            MainGame.Update();
            MainGame.Late_Update();
            MainGame.Render();
            dwTime = GetTickCount();
        }
    }
}
```

- Idle 구간에서만 게임 로직을 수행하도록 구성.
- `MainGame::Initialize()`에서 `BmpMgr`로 배경 비트맵을 등록하고, `SceneMgr`에 첫 씬을 설정.
- 각 씬(`CScene`)은 자체 `Render()`를 가지며 배경·오브젝트·UI를 그린다.

### 결과
- WinAPI 메시지 처리와 게임 로직이 분리되어 입력과 무관하게 일정한 프레임 유지.
- 이후 구현되는 발판, NPC, UI 등 모든 오브젝트가 동일한 씬 구조 위에서 동작.

---

## 3. 발판 시스템 (에디터 → 클라이언트)

### 문제 상황
- 복잡한 맵에서 발판/사다리/밧줄 좌표를 하드코딩하면 작업량과 유지보수 비용이 너무 큼.

### 해결 과정
- 별도의 WinAPI 에디터 프로젝트를 만들어 배경 위에 발판을 찍고 `LineMgr`로 시각화.
- 포토샵에서 찍은 좌표를 `LINEPOINT` 배열로 정리 후 `CLine` 객체로 구성.

```cpp
LINEPOINT tLine[34] = {
    {0, 672}, {1788, 672},
    {321, 614}, {515, 614},
    {357, 436}, {357, 585},  // ROPE
    {435, 238}, {435, 411},
};

m_LineList.push_back(new CLine(tLine[0],  tLine[1],  LINE_FLOOR));
m_LineList.push_back(new CLine(tLine[2],  tLine[3],  LINE_FLOOR));
m_LineList.push_back(new CLine(tLine[26], tLine[27], LINE_ROPE));
```

- 에디터에서 `S` 키로 `.dat` 파일을 저장하고, 클라이언트 `LineMgr::Load_Line()`에서 씬 ID에 따라 해당 파일을 읽어 로드.

### 결과
- 발판 구조를 에디터에서 시각적으로 편집하고, 클라이언트에서는 데이터 파일만 교체하는 파이프라인 확립.

---

## 4. 플레이어 & 발판 충돌

### 문제 상황
- 플레이어가 발판 위에 서거나 점프 후 자연스럽게 착지해야 했음.
- 단순히 Y좌표를 강제로 맞추면 경사·복층 구조에서 움직임이 부자연스러움.

### 해결 과정

```cpp
bool CPlayer::Collision_Line(const list<CLine*>& lines)
{
    for (auto& line : lines)
    {
        float fY = line->Get_Y(m_tInfo.fX);
        if (m_tInfo.fY >= fY && m_tInfo.fY <= fY + m_fFootRange)
        {
            m_tInfo.fY = fY - m_tInfo.fCY * 0.5f; // 발 위치 보정
            m_bJump = false;
            return true;
        }
    }
    return false;
}
```

- 플레이어 중심의 X 좌표를 기준으로 현재 서 있는 발판 선분을 찾고, 해당 선분 Y 좌표에 맞추어 위치를 보정.
- `Update()`에서 입력과 점프 플래그를 처리하고, `Late_Update()`에서 중력·충돌을 처리하여 자연스러운 포물선 후 착지 구현.

### 결과
- 복층 맵에서도 매끄러운 이동과 착지가 가능해졌고, 이후 벽 충돌·낙하 등 물리 로직 확장에 유리한 구조 확보.

---

## 5. 스크롤 & 카메라

### 문제 상황
- 맵이 화면보다 넓어 플레이어를 중심으로 전체 배경/오브젝트를 스크롤해야 했음.
- 맵 끝에서는 카메라를 고정하고 플레이어만 움직이도록 해야 했음.

### 해결 과정
- `ScrollMgr`에 전역 스크롤 값을 두고, 배경/발판/NPC 렌더링에서 모두 같은 오프셋을 사용.
- 씬 크기와 플레이어 RECT를 비교해 카메라 범위를 제한.

```cpp
void CPlayer::Offset()
{
    RECT rc = m_tRect;

    if (rc.left  < m_iMarginX)
        ScrollMgr->Set_ScrollX(0.f);
    else if (rc.right > m_iSceneWidth - m_iMarginX)
        ScrollMgr->Set_ScrollX(m_iSceneWidth - WINCX);
    else
        ScrollMgr->Set_ScrollX(m_tInfo.fX - WINCX * 0.5f);
}
```

### 결과
- 맵 중앙에서는 카메라가 플레이어를 따라 움직이고, 양 끝에서는 카메라가 고정되는 자연스러운 횡스크롤 연출.

---

## 6. NPC & 몬스터 배치 / 씬 전환

### 문제 상황
- 씬 전환 시 이전 씬의 NPC/몬스터가 남거나, 필요한 데이터까지 삭제되는 문제가 발생.

### 해결 과정
- NPC는 이동 없는 `CObj` 파생 클래스로 구현하고, 각 씬의 `Initialize()`에서만 생성.
- 씬 전환 시 `Scene::Remove_All()`로 플레이어를 제외한 오브젝트를 일괄 삭제.

```cpp
void CScene::Remove_All()
{
    list<CObj*> listObj;
    CObjMgr::Get_Instance()->Get_ObjList(listObj); // 플레이어 제외
    for (auto& obj : listObj)
        Safe_Delete(obj);
}
```

### 결과
- 맵 이동 시 NPC/몬스터가 깔끔하게 리셋되고, 되돌아갈 때도 일관된 초기 상태를 유지.

---

## 7. 스프라이트 애니메이션 시스템

### 문제 상황
- 제로, 몬스터, NPC 모두 여러 프레임을 가진 스프라이트 시트를 사용.
- 각 객체마다 별도의 애니메이션 로직을 두면 중복이 심하고 상태 관리가 복잡해짐.

### 해결 과정

```cpp
struct FRAME
{
    int iStartX, iStartY;
    int iEndX;
    int iCurX;
    DWORD dwSpeed;
    DWORD dwTime;
};
```

- `CObj`에 `FRAME m_tFrame`을 두고, `Move_Frame()`에서 시간 기준으로 프레임 자동 전환.
- `Motion_Change()`에서 상태(`STATE`), 방향(`DIR`), 제로 타입(`ZERO_TYPE`) 조합으로 프레임 키와 범위를 설정.

```cpp
void CPlayer::Motion_Change()
{
    if (m_eCurState == m_ePreState && m_pFrameKey) return;

    if (m_eCurState == STATE_IDLE && m_eDir == DIR_RIGHT)
        m_pFrameKey = L"ZERO_ALPHA_IDLE_R";
    else if (m_eCurState == STATE_WALK && m_eDir == DIR_RIGHT)
        m_pFrameKey = L"ZERO_ALPHA_WALK_R";

    m_tFrame = { 0, 0, 7, 0, 100, GetTickCount() };
    m_ePreState = m_eCurState;
}
```

### 결과
- 플레이어·NPC·보스가 공통 애니메이션 시스템을 공유하면서도 상태별 자연스러운 모션 구현.

---

## 8. 제로 태그 시스템 & 스킬

### 문제 상황
- 제로(알파/베타)는 모션·스킬·UI가 다르고, 태그 시스템으로 전환해야 함.
- 알파/베타를 별도 클래스로 나누면 구조가 복잡해지고 참조 교체가 어려워짐.

### 해결 과정
- `CPlayer` 내부에 `ZERO_TYPE`, `STATE`, `DIR` 열거형을 두고 상태를 통합 관리.

```cpp
enum ZERO_TYPE { ZERO_ALPHA, ZERO_BETA };
enum STATE    { STATE_IDLE, STATE_MOVE, STATE_JUMP, STATE_ATTACK };

void CPlayer::Key_Input()
{
    m_ePreState = m_eCurState;
    m_eCurState = STATE_IDLE;

    if (IsKeyDown('X'))          m_eCurState = STATE_ATTACK;
    else if (IsKeyDown(VK_SPACE)) m_eCurState = STATE_JUMP;
    else if (IsKeyDown(VK_LEFT) || IsKeyDown(VK_RIGHT))
        m_eCurState = STATE_MOVE;

    if (IsKeyDown('A')) m_eCurZero = ZERO_ALPHA;
    if (IsKeyDown('S')) m_eCurZero = ZERO_BETA;
}
```

- (제로 타입, 상태, 방향) 조합으로 프레임 키를 결정하고, 스킬은 별도 오브젝트로 생성 후 일정 시간 후 자동 소멸.

### 결과
- 단일 `CPlayer` 클래스에서 제로 알파/베타 전환, 방향, 상태, 스킬 발동까지 모두 관리하는 태그 시스템 완성.

---

## 9. 게이지 UI (Exp / HP / TP / Assist)

### 문제 상황
- HP/TP/경험치/어시스트 게이지는 실시간으로 변해야 하지만, 카메라에 영향을 받지 않는 HUD 형태여야 했음.

### 해결 과정

```cpp
void CExpGauge::Update()
{
    float fRatio = CObjMgr::Get_Instance()->Get_Player()->Get_ExpRatio();
    m_tInfo.fCX = m_fMaxWidth * fRatio;
    __super::Update_Rect();
}
```

- `CUI` / `CUIMgr`를 `CObj` / `CObjMgr`와 유사한 구조로 분리하여 UI 전용 업데이트 루프 구현.
- 어시스트 게이지는 제로 태그 상태와 연동해서 값 변경.

### 결과
- 플레이 스타일과 제로 태그 변화에 따라 HUD 게이지가 즉각 반응하는 UI 구축.

---

## 10. 버튼 & 마우스 커서 UI

### 문제 상황
- 인벤토리/메뉴/보스 입장 UI 등에서 버튼 호버/클릭 상태에 따른 이미지 변경이 필요.
- 마우스 커서도 상황에 따라 다른 애니메이션이 필요.

### 해결 과정

```cpp
void CUIButton::Late_Update()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    if (PtInRect(&m_tRect, pt))
        m_tFrame.iStartX = m_iHoverX;
    else
        m_tFrame.iStartX = m_iNormalX;
}
```

- 버튼을 UI 오브젝트로 구현하고, 마우스 위치와 RECT 충돌 여부로 호버 상태 판단.
- 마우스 커서는 별도의 UI 객체로 구현하여 위치를 계속 추적하고 프레임을 변경.

### 결과
- 실제 메이플과 비슷한 버튼/커서 상호작용 연출.

---

## 11. 보스 패턴 시스템

### 문제 상황
- 카오스 핑크빈이 여러 패턴(레이저, 운석, 독 안개 등)을 일정 주기마다 반복해야 했음.
- 단순 if문만으로는 애니메이션이 끝나기 전에 상태가 바뀌어 패턴이 꼬이는 문제가 발생.

### 해결 과정

```cpp
void CBoss::Attack_Pattern()
{
    DWORD dwTime = GetTickCount() - m_dwStartTime;
    int n = (dwTime / 1000) % 4;

    switch (n)
    {
    case 0: Set_State(STATE_LASER);   break;
    case 1: Set_State(STATE_METEOR);  break;
    case 2: Set_State(STATE_POISON);  break;
    case 3: Set_State(STATE_SUMMON);  break;
    }
}
```

- 패턴별 스킬 이펙트는 bool 플래그로 “한 번만 생성”하도록 제어하고, 애니메이션이 끝나는 시점에서 플래그를 초기화.

### 결과
- 보스가 일정한 로직으로 다양한 패턴을 순환하며 공격하고, 플레이어 스킬 시스템과 동일한 방식으로 관리 가능.

---

## 12. 충돌 처리 (플레이어·몬스터·스킬)

### 문제 상황
- 플레이어 vs 몬스터, 스킬 vs 몬스터, 몬스터 스킬 vs 플레이어 등 다양한 충돌 조합을 처리해야 했음.
- `RECT`를 값으로 반환하면 매 프레임 복사 비용이 발생.

### 해결 과정

```cpp
RECT& CObj::Get_Rect()  // 값이 아닌 참조 반환
```

```cpp
bool CCollisionMgr::Collision_Rect(list<CObj*>& dst, list<CObj*>& src)
{
    for (auto& pDst : dst)
    for (auto& pSrc : src)
    {
        RECT rc;
        if (IntersectRect(&rc, &pDst->Get_Rect(), &pSrc->Get_Rect()))
            return true;
    }
    return false;
}
```

- `CollisionMgr`에서 오브젝트 리스트 간 충돌을 일괄 처리하고, 플레이어의 `Late_Update()`에서 “몬스터와 충돌”, “몬스터 스킬과 충돌”을 각각 분리 처리.

### 결과
- 충돌 로직이 한 곳으로 모여 유지보수가 쉬워지고, 다양한 오브젝트 타입 간 충돌도 쉽게 확장 가능.

---

## 13. 아이템 드롭 & 인벤토리 UI

### 문제 상황
- 필드에서 얻은 아이템이 인벤토리에 반영되어야 하고, UI가 닫혀 있어도 데이터는 유지되어야 함.

### 해결 과정

```cpp
void CPlayer::Pickup(CItem* pItem)
{
    m_listItem.push_back(pItem->Get_ItemData());
    pItem->Set_Dead();
}
```

- 플레이어가 정적 리스트로 아이템 데이터를 들고 있고, 인벤토리 UI는 `I` 키로 열릴 때 리스트를 읽어 슬롯에 반영.
- 슬롯은 버튼 UI 형태로 구현하고, 초기에는 투명 비트맵을 사용하다가 아이템 정보에 따라 스프라이트를 교체.

### 결과
- 필드 → 인벤토리까지의 아이템 흐름 완성 및 UI 토글과 무관한 데이터 유지.

---

## 14. NPC 대화창 & 팝업 UI

### 문제 상황
- 폰트/한글 렌더링 문제로 텍스트를 직접 그리기 어려웠고, 메이플과 유사한 대화창 + 선택지를 구현해야 했음.

### 해결 과정
- 대사 텍스트가 포함된 이미지를 여러 장 만들어 `UI_POPUP`, `UI_BUTTON` 타입으로 관리.
- NPC의 충돌 범위를 넓혀 플레이어가 가까이 접근하면 `SPACE` 입력으로 팝업 생성.
- 버튼 클릭 시 씬 전환, 퀘스트 시작 등 후속 이벤트 실행.

### 결과
- 실제 메이플과 유사한 NPC 대화 플로우 구현, 팝업 UI 시스템을 보스 입장 등 다른 이벤트에도 재사용 가능.

---

## 마무리

이 프로젝트는 기성 엔진 없이 WinAPI만으로 2D 액션 RPG의 핵심 시스템을 직접 구현한 경험으로,  
리소스 추출부터 에디터 제작, 씬·오브젝트·UI 매니저 설계, 보스 패턴/충돌 처리까지 게임 제작 파이프라인 전반을 다룹니다.

자세한 구현은 레포지토리 소스 코드(특히 `Player`, `LineMgr`, `ScrollMgr`, `UIMgr`, `Boss`, `CollisionMgr`)를 참고해 주세요.
