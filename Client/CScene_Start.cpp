#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CCamera.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CBtnUI.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CFixedUI.h"
#include "CGround.h"
#include "CEventMgr.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	
}


void CScene_Start::Enter()
{ 
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	// ----------------------
	//      Object 추가
	// ----------------------
	CFixedUI* MainUI = new CFixedUI;
	MainUI->SetName(L"MainUI");
	Vec2 uiPos =vResolution / 2 - Vec2(150.f, 150.f);
	MainUI->SetPos(uiPos);
	MainUI->SetScale(Vec2(300.f, 300.f));
 
	
	CBtnUI* StartGameUI = new CBtnUI;
	StartGameUI->SetName(L"StartGameUI");
	StartGameUI->SetPos(Vec2(0.f, 0.f));
	StartGameUI->SetScale(Vec2(300.f, 100.f));
	CTexture* starttex = CResMgr::GetInst()->LoadTexture(L"StartUITex", L"texture\\StartUI.bmp");
	StartGameUI->SetTexture(starttex);
	((CBtnUI*)StartGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Start::GameStart);
	MainUI->AddChild(StartGameUI);

	CBtnUI* OptionUI = new CBtnUI;
	OptionUI->SetName(L"EndGameUI");
	OptionUI->SetPos(Vec2(0.f, 100.f));
	OptionUI->SetScale(Vec2(300.f, 100.f));
	CTexture* Optiontex = CResMgr::GetInst()->LoadTexture(L"OPtionUITex", L"texture\\OptionUI.bmp");
	OptionUI->SetTexture(Optiontex);
	((CBtnUI*)OptionUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Start::Option);

	MainUI->AddChild(OptionUI);

	CBtnUI* EndGameUI = new CBtnUI;
	EndGameUI->SetName(L"EndGameUI");
	EndGameUI->SetPos(Vec2(0.f, 200.f));
	EndGameUI->SetScale(Vec2(300.f, 100.f));
	CTexture* EndGametex = CResMgr::GetInst()->LoadTexture(L"EndGametex", L"texture\\ExitUI.bmp");
	EndGameUI->SetTexture(EndGametex);
	((CBtnUI*)EndGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Start::EndGame);
	MainUI->AddChild(EndGameUI);

	AddObject(MainUI, GROUP_TYPE::UI);



	// 충돌 지정

	// Camera Look 지정

	CCamera::GetInst()->SetLookAt(vResolution / 2.f); 
	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}


void CScene_Start::GameStart()
{
	tEvent start = {};
	start.eEven = EVENT_TYPE::SCENE_CHANGE;
	start.lParam = (DWORD)SCENE_TYPE::PLAYGMAE;
	//start.lParam = SCENE_TYPE::PLAYGMAE;

	CEventMgr::GetInst()->AddEvent(start);
}

void CScene_Start::EndGame()
{
	DestroyWindow(CCore::GetInst()->GetMainHwnd());
}

void CScene_Start::Option()
{
	tEvent option = {};
	option.eEven = EVENT_TYPE::SCENE_CHANGE;
	option.lParam = (DWORD)SCENE_TYPE::OPTION;
	//start.lParam = SCENE_TYPE::PLAYGMAE;

	CEventMgr::GetInst()->AddEvent(option);
}
