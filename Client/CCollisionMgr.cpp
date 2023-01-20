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
		// �浹ü�� �������� �ʴ� ���
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{

			// �浹ü�� ���ų�, �ڱ� �ڽŰ� �浹�� ���
			if (nullptr == vecRight[j]->GetCollider()
				|| vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID = {};
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();
			iter = m_mapColInfo.find(ID.ID);



			COLLISION_INFO colinfo = {};
			colinfo._iscollision = false;
			colinfo._LeftDirect = CollisionDirect::NOINFO;
			colinfo._RightDirect = CollisionDirect::NOINFO;

			// �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴ� ��)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, colinfo));
				iter = m_mapColInfo.find(ID.ID);
			}

			if(IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浿 ���̴�.

				if (iter->second._iscollision)
				{
					// �������� �浿 �ϰ� �־���.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �ٵ� ���� �ϳ��� ���� �����̶��, �浹 ���������ش�.
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
					// �������� �浹���� �ʾҴ�.
                    //�ٵ� �����ϳ��� ���� �����̷����, �浹���� ���������� ���
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// ���� ó������ �浹�� ����
					
						// ������⿡�� �浹���� �˻�
						Vec2 pLeftPos = pLeftCol->GetPrevFinalPos();
						Vec2 pRightPos = pRightCol->GetPrevFinalPos();
						Vec2 pLeftScale = pLeftCol->GetScale();
						Vec2 pRightScale = pRightCol->GetScale();

						if (pLeftPos.x > pRightPos.x && pLeftPos.y <= pRightPos.y ) // ����
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
						else if (pLeftPos.x > pRightPos.x && pLeftPos.y > pRightPos.y) // ���ϴ�
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
						else if (pLeftPos.x <= pRightPos.x && pLeftPos.y <= pRightPos.y) // �»��
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
						else if (pLeftPos.x <= pRightPos.x && pLeftPos.y > pRightPos.y) // ���ϴ�
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
				
						// �ڽ��� ���ؿ��� ��� ���⿡�� �浿���� Ȯ��,

						// ���ο��� �浹�� �־�ٰ� �˸�
						pLeftCol->OnCollisionEnter(pRightCol, iter->second._LeftDirect);
						pRightCol->OnCollisionEnter(pLeftCol, iter->second._RightDirect);
						iter->second._iscollision = true;
					}
				}

			}
			else
			{
				// ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second._iscollision)
				{
					// �������� �浹�ϰ� �־���.
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ) �� ���
	
	UINT iCol = (UINT)_eRight;  // Column ��
	UINT iRow = (UINT)_eLeft;   // Row    ��
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

