#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();


	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, COLLISION_INFO>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// 충돌체를 보유하지 않는 경우
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{

			// 충돌체가 없거나, 자기 자신과 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID = {};
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);



			COLLISION_INFO colinfo = {};
			colinfo._iscollision = false;
			colinfo._LeftDirect = CollisionDirect::NOINFO;
			colinfo._RightDirect = CollisionDirect::NOINFO;

			// 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다 로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, colinfo));
				iter = m_mapColInfo.find(ID.ID);
			}

			if(IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충동 중이다.

				if (iter->second._iscollision)
				{
					// 이전에도 충동 하고 있었다.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// 근데 둘중 하나가 삭제 예정이라면, 충돌 해제시켜준다.
						pLeftCol->OnCollisionExit(pRightCol, iter->second._LeftDirect);
						pRightCol->OnCollisionExit(pLeftCol, iter->second._RightDirect);
						iter->second._iscollision = false;
						iter->second._LeftDirect = CollisionDirect::NOINFO;
						iter->second._RightDirect = CollisionDirect::NOINFO;
					}
					else
					{ 
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					// 이전에는 충돌하지 않았다.
                    //근데 둘중하나가 삭제 예정이러라면, 충돌하지 않은것으로 취급
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// 둘이 처음으로 충돌한 시점
					
						// 어느방향에서 충돌한지 검사
						Vec2 pLeftPos = pLeftCol->GetPrevFinalPos();
						Vec2 pRightPos = pRightCol->GetPrevFinalPos();
						Vec2 pLeftScale = pLeftCol->GetScale();
						Vec2 pRightScale = pRightCol->GetScale();

						if (pLeftPos.x > pRightPos.x && pLeftPos.y <= pRightPos.y ) // 우상단
						{
							Vec2 pLeftVertex = pLeftPos + Vec2(-pLeftScale.x / 2, +pLeftScale.y / 2);
							Vec2 pRightVertex = pRightPos + Vec2(pRightScale.x / 2, -pRightScale.y / 2);
							if (pLeftVertex.y < pRightVertex.y)
							{
								iter->second._LeftDirect = CollisionDirect::DOWN;
								iter->second._RightDirect = CollisionDirect::UP;
							}
							else
							{
								iter->second._LeftDirect = CollisionDirect::LEFT;
								iter->second._RightDirect = CollisionDirect::RIGHT;
							}
						}
						else if (pLeftPos.x > pRightPos.x && pLeftPos.y > pRightPos.y) // 우하단
						{
							Vec2 pLeftVertex = pLeftPos + Vec2(-pLeftScale.x / 2, -pLeftScale.y / 2);
							Vec2 pRightVertex = pRightPos + Vec2(pRightScale.x / 2, +pRightScale.y / 2);
							if (pLeftVertex.y < pRightVertex.y)
							{
								iter->second._LeftDirect = CollisionDirect::LEFT;
								iter->second._RightDirect = CollisionDirect::RIGHT;
							}
							else
							{
								iter->second._LeftDirect = CollisionDirect::UP;
								iter->second._RightDirect = CollisionDirect::DOWN;
							}
						}
						else if (pLeftPos.x <= pRightPos.x && pLeftPos.y <= pRightPos.y) // 좌상단
						{
							Vec2 pLeftVertex = pLeftPos + Vec2(+pLeftScale.x / 2, +pLeftScale.y / 2);
							Vec2 pRightVertex = pRightPos + Vec2(-pRightScale.x / 2, -pRightScale.y / 2);
							if (pLeftVertex.y < pRightVertex.y)
							{
								iter->second._LeftDirect = CollisionDirect::DOWN;
								iter->second._RightDirect = CollisionDirect::UP;
							}
							else
							{
								iter->second._LeftDirect = CollisionDirect::RIGHT;
								iter->second._RightDirect = CollisionDirect::LEFT;
							}
						}
						else if (pLeftPos.x <= pRightPos.x && pLeftPos.y > pRightPos.y) // 좌하단
						{
							Vec2 pLeftVertex = pLeftPos + Vec2(+pLeftScale.x / 2, -pLeftScale.y / 2);
							Vec2 pRightVertex = pRightPos + Vec2(-pRightScale.x / 2, +pRightScale.y / 2);
							if (pLeftVertex.y < pRightVertex.y)
							{
								iter->second._LeftDirect = CollisionDirect::RIGHT;
								iter->second._RightDirect = CollisionDirect::LEFT;
							}
							else
							{
								iter->second._LeftDirect = CollisionDirect::UP;
								iter->second._RightDirect = CollisionDirect::DOWN;
							}
						}
						else
						{
							assert(nullptr);
						}
				
						// 자신의 기준에서 어느 방향에서 충동한지 확인,

						// 서로에게 충돌이 있어났다고 알림
						pLeftCol->OnCollisionEnter(pRightCol, iter->second._LeftDirect);
						pRightCol->OnCollisionEnter(pLeftCol, iter->second._RightDirect);
						iter->second._iscollision = true;
					}
				}

			}
			else
			{
				// 현재 충돌하고 있지 않다.
				if (iter->second._iscollision)
				{
					// 이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol, iter->second._LeftDirect);
					pRightCol->OnCollisionExit(pLeftCol, iter->second._RightDirect);
					iter->second._iscollision = false;
					iter->second._LeftDirect = CollisionDirect::NOINFO;
					iter->second._RightDirect = CollisionDirect::NOINFO;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos =_pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트) 로 사용
	
	UINT iCol = (UINT)_eRight;  // Column 열
	UINT iRow = (UINT)_eLeft;   // Row    행
	if (iRow > iCol)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

