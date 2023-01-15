#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "SelectGDI.h"

void CMissile::update()
{
}



CMissile::CMissile()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(10.f, 10.f));
}

CMissile::~CMissile()
{
}
void CMissile::render(HDC _dc)
{
	Vec2 m_vPos = GetPos();
	Vec2 m_vScale = GetScale();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	SelectGDI gdi(_dc, BRUSH_TYPE::DARKBLUE);
	Ellipse(_dc
		, (int)(vRenderPos.x + m_vScale.x / 2.f)
		, (int)(vRenderPos.y + m_vScale.y / 2.f)
		, (int)(vRenderPos.x - m_vScale.x / 2.f)
		, (int)(vRenderPos.y - m_vScale.y / 2.f));

	component_render(_dc);

}
