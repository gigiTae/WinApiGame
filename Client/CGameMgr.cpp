#include "pch.h"
#include "CGameMgr.h"
#include "CPlayer.h"
#include "CNumberUI.h"

CGameMgr::CGameMgr()
	:mPlayer(nullptr)
	,mHpUI(nullptr)
{

}

CGameMgr::~CGameMgr()
{

}

void CGameMgr::GameOver()
{
	
}

void CGameMgr::CheckPlayerLife()
{
	int playerhp =mPlayer->GetPlayerHp();
	mHpUI->SetNumber(playerhp);

	if (0 >= playerhp)
	{
		GameOver();
	}

}

void CGameMgr::update()
{
	CheckPlayerLife();
}
