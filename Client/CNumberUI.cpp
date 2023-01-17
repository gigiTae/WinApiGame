#include "pch.h"
#include "CNumberUI.h"
#include "CTexture.h"
#include "CResMgr.h"


CNumberUI::CNumberUI()
	:CUI(false)
	, m_Number(0)
	, m_UITex(nullptr)
{
	m_UITex = CResMgr::GetInst()->LoadTexture(L"numberuiTex", L"texture\\numberui.bmp");
}

CNumberUI::~CNumberUI()
{
}

void CNumberUI::render(HDC _dc)
{
	if (9 < m_Number)
		assert(nullptr);

	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	int iWidth = (int)m_UITex->Whidth();
	int iHeight = (int)m_UITex->Height();
	
	int nXOriginDest = m_Number * 50;



	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, 50, 100
		, m_UITex->GetDC()
		, nXOriginDest, 0, 50, iHeight
		, RGB(255, 0, 255));

}