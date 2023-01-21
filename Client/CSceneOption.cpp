#include "pch.h"
#include "CSceneOption.h"

#include "CBtnUI.h"
#include "CScene_GameOver.h"
#include "CResMgr.h"

CSceneOption::CSceneOption()
{
}

CSceneOption::~CSceneOption()
{
}

void CSceneOption::Enter()
{
	CBtnUI* ExitBtn = new CBtnUI;
	CTexture* exittex = CResMgr::GetInst()->LoadTexture(L"exitTex", L"texture\\Exit.bmp");
	ExitBtn->SetPos(Vec2(20.f, 20.f));
	ExitBtn->SetTexture(exittex);
	ExitBtn->SetScale(Vec2(150.f, 100.f));
	((CBtnUI*)ExitBtn)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_GameOver::ExitGame);
	AddObject(ExitBtn, GROUP_TYPE::UI);
}

void CSceneOption::Exit()
{
	DeleteAll();
}