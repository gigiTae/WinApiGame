#include "pch.h"
#include "CScene_GameOver.h"
#include "CBtnUI.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "CFixedUI.h"
#include "CPathMgr.h"
#include "CNumberUI.h"

void CScene_GameOver::Enter()
{ 
	// ���� �����ϱ�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"data\\score.info";
	FILE* pFile = nullptr;

	// bestscore �ҷ�����
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	int NowScore = 0;
	int BestScore = 0;
	fread(&BestScore, sizeof(int), 1, pFile);
	fread(&NowScore, sizeof(int), 1, pFile);
	fclose(pFile);

	// NowScorUI

	CFixedUI* NowTimeUI = new CFixedUI;
	CTexture* Timetex = CResMgr::GetInst()->LoadTexture(L"TIMEUITex", L"texture\\TIMEUI.bmp");
	NowTimeUI->SetTexture(Timetex);
	NowTimeUI->SetPos(Vec2(100.f, 250.f));
	AddObject(NowTimeUI, GROUP_TYPE::UI);

	CFixedUI* BestUI = new CFixedUI;
	CTexture* Besttex = CResMgr::GetInst()->LoadTexture(L"BestTex", L"texture\\BestUI.bmp");
	BestUI->SetTexture(Besttex);
	BestUI->SetPos(Vec2(450.f, 250.f));
	AddObject(BestUI, GROUP_TYPE::UI);

	{
	int �����ڸ� = NowScore / 100;
	int �����ڸ� = (NowScore - �����ڸ� * 100) / 10;
	int �����ڸ� = (NowScore - �����ڸ� * 100) % 10;

	CNumberUI* FirstUI = new CNumberUI;
	FirstUI->SetNumber(�����ڸ�);
	FirstUI->SetPos(Vec2(250.f, 250.f));
	FirstUI->SetScale(Vec2(50.f, 100.f));

	AddObject(FirstUI, GROUP_TYPE::UI);

	CNumberUI* SecondUI = new CNumberUI;
	SecondUI->SetNumber(�����ڸ�);
	SecondUI->SetPos(Vec2(300.f, 250.f));
	SecondUI->SetScale(Vec2(50.f, 100.f));

	AddObject(SecondUI, GROUP_TYPE::UI);

	CNumberUI* ThirdUI = new CNumberUI;
	ThirdUI->SetNumber(�����ڸ�);
	ThirdUI->SetPos(Vec2(350.f, 250.f));
	ThirdUI->SetScale(Vec2(50.f, 100.f));
	
	AddObject(ThirdUI, GROUP_TYPE::UI);

	}

	// BestScoreUI

	{
		int �����ڸ� = BestScore / 100;
		int �����ڸ� = (BestScore - �����ڸ� * 100) / 10;
		int �����ڸ� = (BestScore - �����ڸ� * 100) % 10;

		CNumberUI* FirstUI = new CNumberUI;
		FirstUI->SetNumber(�����ڸ�);
		FirstUI->SetPos(Vec2(600.f, 250.f));
		FirstUI->SetScale(Vec2(50.f, 100.f));
		AddObject(FirstUI, GROUP_TYPE::UI);
		CNumberUI* SecondUI = new CNumberUI;
		SecondUI->SetNumber(�����ڸ�);
		SecondUI->SetPos(Vec2(650.f, 250.f));
		SecondUI->SetScale(Vec2(50.f, 100.f));
		AddObject(SecondUI, GROUP_TYPE::UI);
		CNumberUI* ThirdUI = new CNumberUI;
		ThirdUI->SetNumber(�����ڸ�);
		ThirdUI->SetPos(Vec2(700.f, 250.f));
		ThirdUI->SetScale(Vec2(50.f, 100.f));
		AddObject(ThirdUI, GROUP_TYPE::UI);
	}


	CFixedUI* GameOverUI = new CFixedUI;
	CTexture* GameOvertex = CResMgr::GetInst()->LoadTexture(L"GameOverTex", L"texture\\GameOverUI.bmp");
	GameOverUI->SetTexture(GameOvertex);
	GameOverUI->SetPos(Vec2(250.f, 0.f));
	AddObject(GameOverUI, GROUP_TYPE::UI);

	// ������ ��ư
	CBtnUI* ExitGameUI = new CBtnUI;
	CTexture* exittex = CResMgr::GetInst()->LoadTexture(L"exitTex", L"texture\\Exit.bmp");
	ExitGameUI->SetTexture(exittex);
	ExitGameUI->SetName(L"StartGameUI");
	ExitGameUI->SetPos(Vec2(500.f, 400.f));
	ExitGameUI->SetScale(Vec2(150.f, 100.f));
	((CBtnUI*)ExitGameUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_GameOver::ExitGame);
	AddObject(ExitGameUI,GROUP_TYPE::UI);

	//�ٽ��ϱ� ��ư
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
