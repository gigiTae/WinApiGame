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
#include "CNumberUI.h"
#include "CTimeMgr.h"

#include "CGameMgr.h"
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

	CGameMgr::GetInst()->SetmPlayer(Player);

	// ===================
    //      TIME  UI
    // ===================
	CFixedUI* TimeUI = new CFixedUI;
	CTexture* leveltex = CResMgr::GetInst()->LoadTexture(L"TIMEUITex", L"texture\\TIMEUI.bmp");
	TimeUI->SetTexture(leveltex);
	TimeUI->SetPos(Vec2(0.f, 0.f));
	TimeUI->SetScale(Vec2(150.f, 100.f));
	Panel->AddChild(TimeUI);

	CNumberUI* numUI = new CNumberUI;
	numUI->SetNumber(3);
	numUI->SetPos(Vec2(100.f, 200.f));
	numUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(numUI);

	CGameMgr::GetInst()->SetmHpUI(numUI);

	// ===================
	//       格见 UI
	// ===================
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

	CNumberUI* FirstnumUI = new CNumberUI;
	FirstnumUI->SetNumber(0);
	FirstnumUI->SetPos(Vec2(0.f, 100.f));
	FirstnumUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(FirstnumUI);
	CGameMgr::GetInst()->SetHundreadNum(FirstnumUI);

	CNumberUI* SecondUI = new CNumberUI;
	SecondUI->SetNumber(0);
	SecondUI->SetPos(Vec2(50.f, 100.f));
	SecondUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(SecondUI);
	CGameMgr::GetInst()->SetTneNum(SecondUI);

	CNumberUI* ThirdnumUI = new CNumberUI;
	ThirdnumUI->SetNumber(0);
	ThirdnumUI->SetPos(Vec2(100.f, 100.f));
	ThirdnumUI->SetScale(Vec2(50.f, 100.f));
	Panel->AddChild(ThirdnumUI);
	CGameMgr::GetInst()->SetOneNum(ThirdnumUI);


	// ========================
	//       STOP/ Play UI
	// ========================
	CBtnUI* StopUI = new CBtnUI;
	CTexture* stoptex = CResMgr::GetInst()->LoadTexture(L"stopTex", L"texture\\StopUI.bmp");
	StopUI->SetTexture(stoptex);
	StopUI->SetName(L"StartGameUI");
	StopUI->SetPos(Vec2(0.f, 300.f));
	StopUI->SetScale(Vec2(75.f, 100.f));
	((CBtnUI*)StopUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_PlayGame::GameStop);
	Panel->AddChild(StopUI);

	CBtnUI* PlayUI = new CBtnUI;
	CTexture* playtex = CResMgr::GetInst()->LoadTexture(L"PlayTex", L"texture\\PlayUI.bmp");
	PlayUI->SetTexture(playtex);
	PlayUI->SetName(L"StartGameUI");
	PlayUI->SetPos(Vec2(75.f, 300.f));
	PlayUI->SetScale(Vec2(75.f, 100.f));
	((CBtnUI*)PlayUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_PlayGame::GamePlay);
	Panel->AddChild(PlayUI);



	// ==================
	//       EXIT UI
	// ==================
	CBtnUI* ExitGameUI = new CBtnUI;
	CTexture* exittex = CResMgr::GetInst()->LoadTexture(L"exitTex", L"texture\\Exit.bmp");
	ExitGameUI->SetTexture(exittex);
	ExitGameUI->SetName(L"StartGameUI");
	ExitGameUI->SetPos(Vec2(0.f, 400.f));
	ExitGameUI->SetScale(Vec2(150.f, 90.f));
	((CBtnUI*)ExitGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_PlayGame ::EndGame);
	Panel->AddChild(ExitGameUI);

	AddObject(Panel, GROUP_TYPE::UI);


	// ==================
	//       面倒 眉农
	// ==================
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::TILE);
	CCamera::GetInst()->SetLookAt(Player->GetPos());
}

void CScene_PlayGame::Exit()
{
	DeleteAll();
	PlayTime = 0.f;
	GamePlay();
}

void CScene_PlayGame::update()
{
	bool gameover = CGameMgr::GetInst()->IsGameOver();

	if (gameover == true)
	{
		tEvent eve = {};
		eve.eEven = EVENT_TYPE::SCENE_CHANGE;
		eve.lParam = (DWORD_PTR)SCENE_TYPE::GAMEOVER;

		CGameMgr::GetInst()->SetGameOver(false);
		CEventMgr::GetInst()->AddEvent(eve);
	}

	CScene::update();
	if (false == IsGameStop())
		PlayTime += fDT;
	CGameMgr::GetInst()->SetNowTime(PlayTime);
	CGameMgr::GetInst()->update();

	



}

CScene_PlayGame::CScene_PlayGame()
	:PlayTime(0.f)
{
}

CScene_PlayGame::~CScene_PlayGame()
{
}
