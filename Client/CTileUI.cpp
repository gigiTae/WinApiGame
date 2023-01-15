#include "pch.h"
#include "CTileUI.h"
#include "CUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CScene.h"
#include "CScene_Tool.h"

#include "CkeyMgr.h"

CTileUI::CTileUI()
	:CUI(false)
	, m_pTex(nullptr)
	, m_pScene(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"TileTex", L"texture\\GameTile.bmp");
}

CTileUI::~CTileUI()
{
}

void CTileUI::render(HDC _dc)
{
	CUI::render(_dc);
	
	int iWidth = (int)m_pTex->Whidth();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetFinalPos();

	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));


}


void CTileUI::MouseLbtnClicked()
{
	int ImgIdx = -1;

	Vec2 MousePos =CKeyMgr::GetInst()->GetMousePos();
	Vec2 TilePos = GetFinalPos();

	Vec2 CurPos = MousePos - TilePos;
	int x=(int)CurPos.x / TILE_SIZE;
	int y=(int)CurPos.y / TILE_SIZE;

	ImgIdx = 3 * y + x;
	m_pScene->SetImgIdx(ImgIdx);
}