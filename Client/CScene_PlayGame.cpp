#include "pch.h"
#include "CScene_PlayGame.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CCore.h"
#include "CCollisionMgr.h"
#include "CFixedUI.h"
#include "CResMgr.h"
#include "CBtnUI.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CMonster.h"
#include "CMonFactory.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene.h"
#include "CEventMgr.h"

void CScene_PlayGame::EndGame()
{
	tEvent option = {};
	option.eEven = EVENT_TYPE::SCENE_CHANGE;
	option.lParam = (DWORD)SCENE_TYPE::START;
	//start.lParam = SCENE_TYPE::PLAYGMAE;

	CEventMgr::GetInst()->AddEvent(option);
}

void CScene_PlayGame::Enter()
{
	LoadTile(L"tile\\GameTile");

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2(465.f, 250.f));
	Player->SetName(L"Player");
	Player->SetScale(Vec2(50.f, 50.f));

	AddObject(Player, GROUP_TYPE::PLAYER);

	CFixedUI* Panel = new CFixedUI;
	Panel->SetPos(Vec2(800.f, 20.f));
	Panel->SetScale(Vec2(150.f, 510.f));
	

	CFixedUI* LevelUI = new CFixedUI;
	CTexture* leveltex = CResMgr::GetInst()->LoadTexture(L"LevelUITex", L"texture\\levelUI.bmp");
	LevelUI->SetTexture(leveltex);
	LevelUI->SetPos(Vec2(0.f, 0.f));
	LevelUI->SetScale(Vec2(150.f, 100.f));
	Panel->AddChild(LevelUI);

	CFixedUI* LifeUI = new CFixedUI;
	CTexture* lifetex = CResMgr::GetInst()->LoadTexture(L"lifeUITex", L"texture\\life.bmp");
	LifeUI->SetTexture(lifetex);
	LifeUI->SetPos(Vec2(0.f, 200.f));
	LifeUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(LifeUI);

	CFixedUI* xUI = new CFixedUI;
	CTexture* xtex = CResMgr::GetInst()->LoadTexture(L"xUITex", L"texture\\x.bmp");
	xUI->SetTexture(xtex);
	xUI->SetPos(Vec2(50.f, 200.f));
	xUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(xUI);


	CFixedUI* LifeNumUI = new CFixedUI;
	CTexture* numtex = CResMgr::GetInst()->LoadTexture(L"numTex", L"texture\\3.bmp");
	LifeNumUI->SetTexture(numtex);
	LifeNumUI->SetPos(Vec2(100.f, 200.f));
	LifeNumUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(LifeNumUI);

	CBtnUI* ExitGameUI = new CBtnUI;
	CTexture* exittex = CResMgr::GetInst()->LoadTexture(L"exitTex", L"texture\\Exit.bmp");
	ExitGameUI->SetTexture(exittex);
	ExitGameUI->SetName(L"StartGameUI");
	ExitGameUI->SetPos(Vec2(0.f, 400.f));
	ExitGameUI->SetScale(Vec2(150.f, 90.f));
	((CBtnUI*)ExitGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_PlayGame ::EndGame);
	Panel->AddChild(ExitGameUI);

	AddObject(Panel, GROUP_TYPE::UI);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::TILE);
	CCamera::GetInst()->SetLookAt(Player->GetPos());
}

void CScene_PlayGame::Exit()
{
	DeleteAll();
}

CScene_PlayGame::CScene_PlayGame()
{
}

CScene_PlayGame::~CScene_PlayGame()
{
}
