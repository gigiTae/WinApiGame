#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "CTimeMgr.h"

CRigidBody::CRigidBody()
	:m_pOwner(nullptr)
	,m_vForce{}
	,m_fMass(1.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// ���� ũ��
	float fForce = m_vForce.Length();
	
	if (0.f != fForce)
	{


	// ���� ����
	m_vForce.Nomalize();

	// ���ӵ��� ũ��
	float m_fAccele = fForce / m_fMass;

	// ���ӵ�
	m_vAccel = m_vForce * m_fAccele;

	// �ӵ�
	m_vVelocity += m_vAccel*fDT;
	}

	// �ӵ��� ���� �̵�
	Move();
	// �� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{

	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		// �̵� ����
		Vec2 vDir = m_vVelocity;
		vDir.Nomalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos += vDir * fSpeed * fDT;

		m_pOwner->SetPos(vPos);
	}

}