#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "SelectGDI.h"
#include "CRigidBody.h"

#include "CCollisionMgr.h"


CMissile::CMissile()
	:vDirect(Vec2(0.f,0.f))
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));
	GetRigidBody();

}

CMissile::~CMissile()
{
}
void CMissile::render(HDC _dc)
{
	Vec2 m_vPos = GetPos();
	Vec2 m_vScale = GetScale();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	SelectGDI pen(_dc, PEN_TYPE::RED);
	SelectGDI gdi(_dc, BRUSH_TYPE::RED);
	Ellipse(_dc
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f)
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f));

	//component_render(_dc);

}

void CMissile::OnCollisionEnter(CCollider* _pOther, CollisionDirect _direct)
{
	GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
	if (_direct == CollisionDirect::LEFT)
	{
		if (vDirect.x < 0)
			vDirect.x = -vDirect.x;
	}
	else if (_direct == CollisionDirect::RIGHT)
	{
		if (vDirect.x > 0)
			vDirect.x = -vDirect.x;
	}
	else if (_direct == CollisionDirect::DOWN)
	{
		if (vDirect.y > 0)
			vDirect.y = -vDirect.y;
	}
	else if (_direct == CollisionDirect::UP)
	{
		if (vDirect.y < 0)
			vDirect.y = -vDirect.y;
	}
}

void CMissile::update()
{
	Vec2 Force = vDirect * 20000;
	GetRigidBody()->AddForce(Force);

}


