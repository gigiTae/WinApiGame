#include "pch.h"
#include "CScene_GameOver.h"
#include "CBtnUI.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CFixedUI.h"

void CScene_GameOver::Enter()
{ 
	CFixedUI* GameOverUI = new CFixedUI;
	CTexture* GameOvertex = CResMgr::GetInst()->LoadTexture(L"GameOverTex", L"texture\\GameOverUI.bmp");
	GameOverUI->SetTexture(GameOvertex);
	GameOverUI->SetPos(Vec2(250.f, 100.f));
	AddObject(GameOverUI, GROUP_TYPE::UI);

	// 나가기 버튼
	CBtnUI* ExitGameUI = new CBtnUI;
	CTexture* exittex = CResMgr::GetInst()->LoadTexture(L"exitTex", L"texture\\Exit.bmp");
	ExitGameUI->SetTexture(exittex);
	ExitGameUI->SetName(L"StartGameUI");
	ExitGameUI->SetPos(Vec2(500.f, 400.f));
	ExitGameUI->SetScale(Vec2(150.f, 100.f));
	((CBtnUI*)ExitGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_GameOver::ExitGame);
	AddObject(ExitGameUI,GROUP_TYPE::UI);

	//다시하기 버튼
	CBtnUI* RetryGameUI = new CBtnUI;
	CTexture* Retrytex = CResMgr::GetInst()->LoadTexture(L"RetryTex", L"texture\\RetryUI.bmp");
	RetryGameUI->SetTexture(Retrytex);
	RetryGameUI->SetName(L"StartGameUI");
	RetryGameUI->SetPos(Vec2(250.f, 400.f));
	RetryGameUI->SetScale(Vec2(150.f, 100.f));
	((CBtnUI*)RetryGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_GameOver::RetryGame);
	AddObject(RetryGameUI, GROUP_TYPE::UI);
}

void CScene_GameOver::Exit()
{
	DeleteAll();
}

void CScene_GameOver::RetryGame()
{
	tEvent eve = {};
	eve.eEven = EVENT_TYPE::SCENE_CHANGE;
	eve.lParam = (DWORD_PTR)SCENE_TYPE::PLAYGMAE;
	CEventMgr::GetInst()->AddEvent(eve);

}

void CScene_GameOver::ExitGame()
{
	tEvent eve = {};
	eve.eEven = EVENT_TYPE::SCENE_CHANGE;
	eve.lParam = (DWORD_PTR)SCENE_TYPE::START;
	CEventMgr::GetInst()->AddEvent(eve);

}

CScene_GameOver::CScene_GameOver()
{
}

CScene_GameOver::~CScene_GameOver()
{
}
