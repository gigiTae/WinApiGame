#include "pch.h"
#include "CScene_PlayGame.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CCore.h"



void CScene_PlayGame::Enter()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CPlayer* Player = new CPlayer;
	Player->SetPos(Vec2(vResolution.x, vResolution.y));
	Player->SetName(L"Player");
	Player->SetScale(Vec2(50.f, 50.f));

	AddObject(Player, GROUP_TYPE::PLAYER);

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
