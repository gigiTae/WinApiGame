#include "pch.h"
#include "CFixedUI.h"
#include "CCamera.h"
#include "SelectGDI.h"
#include "CTexture.h"
#include "CUI.h"

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
	CTexture* m_pTex= GetTexture();
	{
		SelectGDI brush(_dc, BRUSH_TYPE::WHITE);
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	if (nullptr != m_pTex)
	{
		int iWidth = (int)m_pTex->Whidth();
		int iHeight = (int)m_pTex->Height();
		TransparentBlt(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, iWidth, iHeight
			, m_pTex->GetDC()
			, 0, 0, iWidth, iHeight
			, RGB(255, 0, 255));
	}
	// child ui render
	render_child(_dc);
}