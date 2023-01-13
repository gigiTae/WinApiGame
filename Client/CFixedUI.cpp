#include "pch.h"
#include "CFixedUI.h"
#include "CCamera.h"
#include "SelectGDI.h"


CFixedUI::CFixedUI()
	:CUI(false)
{
}

CFixedUI::~CFixedUI()
{
}


void CFixedUI::update()
{
}

void CFixedUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	{
		SelectGDI pen(_dc, PEN_TYPE::SKYBLUE);
		SelectGDI brush(_dc, BRUSH_TYPE::SKYBLUE);
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	// child ui render
	render_child(_dc);
}