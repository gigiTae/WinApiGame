#include "pch.h"
#include "CScene_PlayGame.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CCore.h"
#include "CCollisionMgr.h"

#include "CMonster.h"
#include "CMonFactory.h"


void CScene_PlayGame::Enter()
{
	LoadTile(L"tile\\GameTile");

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2(465.f, 250.f));
	Player->SetName(L"Player");
	Player->SetScale(Vec2(50.f, 50.f));

	AddObject(Player, GROUP_TYPE::PLAYER);

	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NOMAL, Vec2(vResolution.x, vResolution.y+100));
	AddObject(pMon, GROUP_TYPE::MONSTER);


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::TILE);
	CCamera::GetInst()->SetLookAt(Player->GetPos());
}

void CScene_PlayGame::Exit()
{
}

CScene_PlayGame::CScene_PlayGame()
{
}

CScene_PlayGame::~CScene_PlayGame()
{
}
