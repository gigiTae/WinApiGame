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
	int 백의자리 = (int)NowTime / 100;
	int 십의자리 = ((int)NowTime-백의자리*100)/10;
	int 일의자리 = ((int)NowTime - 백의자리 * 100)%10;

	TimeHundreadNum->SetNumber(백의자리);
	TimeTenNum->SetNumber(십의자리);
	TimeOneNum->SetNumber(일의자리);

}

void CGameMgr::update()
{
	CheckPlayerLife();
	CheckTime();
}
