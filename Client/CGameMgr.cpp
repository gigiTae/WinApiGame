#include "pch.h"
#include "CGameMgr.h"
#include "CPlayer.h"
#include "CNumberUI.h"
#include "CEventMgr.h"

CGameMgr::CGameMgr()
	:mPlayer(nullptr)
	,mHpUI(nullptr)
	,TimeHundreadNum(nullptr)
	,TimeOneNum(nullptr)
	,TimeTenNum(nullptr)
	,NowTime(0.f)
	,GameOver(false)
{

}

CGameMgr::~CGameMgr()
{

}

void CGameMgr::CheckPlayerLife()
{
	int playerhp =mPlayer->GetPlayerHp();
	mHpUI->SetNumber(playerhp);

	if (0 >= playerhp)
	{
		GameOver= true;
	}

}

void CGameMgr::CheckTime()
{
	int �����ڸ� = (int)NowTime / 100;
	int �����ڸ� = ((int)NowTime-�����ڸ�*100)/10;
	int �����ڸ� = ((int)NowTime - �����ڸ� * 100)%10;

	TimeHundreadNum->SetNumber(�����ڸ�);
	TimeTenNum->SetNumber(�����ڸ�);
	TimeOneNum->SetNumber(�����ڸ�);

}

void CGameMgr::update()
{
	CheckPlayerLife();
	CheckTime();
}
