#include "pch.h"
#include "CUI.h"

#include "CkeyMgr.h"
#include "CCamera.h"
#include "CCore.h"
#include "CTexture.h"
#include "CResMgr.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_ParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_pTex(nullptr)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_ParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_pTex(_origin.m_pTex)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);  
}

void CUI::update()
{

	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();

	// UI의 최종 좌표를 구한다.
	m_vFinalPos = GetPos();
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	// UI Mouse 체크
	MouseOnCheck();



	finalupdate_child();
}

void CUI::render(HDC _dc)
{
	Vec2 vPos =GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	if (m_bLbtnDown)
	{
	SelectGDI select(_dc, BRUSH_TYPE::WHITE);
	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	}
	else {
		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}

	// 텍스처 업데이트
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


void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
	
} 

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{

}

