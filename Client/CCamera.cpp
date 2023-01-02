#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CkeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(2.f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
{	  

}

CCamera::~CCamera()
{

}

void CCamera::update()
{
	if(m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	CalDiff();

}

void CCamera::CalDiff()
{
	// ���� LookAt �� ������ ���� ���� �����ؼ� ������ LookAt �� ���Ѵ�.

	m_fAccTime += fDT;
	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPreLookAt;
		if (vLookDir.x == 0 && vLookDir.y == 0)
		{
		}
		else
			vLookDir.Nomalize();
		m_vCurLookAt = m_vPreLookAt + vLookDir * m_fSpeed * fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPreLookAt = m_vCurLookAt;
}
