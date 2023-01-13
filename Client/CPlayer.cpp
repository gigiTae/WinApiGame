#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CkeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CGravity.h"

#include "CRigidBody.h"


CPlayer::CPlayer()
	: m_pTex(nullptr)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(KEY::S)
	, m_ePrevState(PLAYER_STATE::IDLE)
	, m_MissileTimer(0.f)

{
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"Player1Tex", L"texture\\c1.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 24.f));
	GetCollider()->SetScale(Vec2(32.f, 28.f));
	
	CreateRigidBody();

	// Texture 로딩하기
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\PlayerAnimation.bmp");
	
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 192.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.15f, 6);
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->Play(L"IDLE", true);
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_gravity();

	update_move();

	update_state();

	update_animation();


	GetAnimator()->update();

	m_MissileTimer += fDT;
	if (m_MissileTimer >= 5.f)
	{
		CreateMissile();
		m_MissileTimer -= 5.f;
	}

	m_ePrevState = m_eCurState;
}

void CPlayer::render(HDC _dc)
{

	// 컴포넌트 (충돌체 ,etc...)가 있는경우
	component_render(_dc);
}

void CPlayer::update_state()
{
	if (GetRigidBody()->GetVelocity() == Vec2(0.f, 0.f))
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

	if (KEY_TAP(KEY::A))
	{
		m_iDir = KEY::A;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::D))
	{
		m_iDir = KEY::D;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::W))
	{
		m_iDir = KEY::W;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::S))
	{
		m_iDir = KEY::S;
		m_eCurState = PLAYER_STATE::WALK;
	}

	
}

void CPlayer::update_move()
{

	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f, -1500.f));
	}
	if (KEY_HOLD(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 1500.f));
	}
	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-1500.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(1500.f, 0.f));
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState != m_eCurState)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		GetAnimator()->Play(L"IDLE", true);
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == KEY::D)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else if (m_iDir == KEY::A)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else if (m_iDir == KEY::W)
			GetAnimator()->Play(L"WALK_UP", true);
		else if (m_iDir == KEY::S)
			GetAnimator()->Play(L"WALK_DOWN", true);
	}

		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	default:

		break;
	}
}

void CPlayer::update_gravity()
{
//	GetRigidBody()->AddForce(Vec2(0.f,500.f));

}

void CPlayer::CreateMissile()
{
	//CMissile* NewMissile = new CMissile;
}



//int iWidth = (int)m_pTex->Whidth();
//int iHeight = (int)m_pTex->Height();

//Vec2 vPos = GetPos();
//vPos = CCamera::GetInst()->GetRenderPos(vPos);
//
//BLENDFUNCTION bf = {};
//bf.BlendOp = AC_SRC_OVER;
//bf.BlendFlags = 0;
//bf.AlphaFormat = 0;
//bf.SourceConstantAlpha = 126;

//AlphaBlend(_dc
//	, (int)(vPos.x - (float)(iWidth / 2))
//	, (int)(vPos.y - (float)(iHeight / 2))
//	, iWidth, iHeight
//	, m_pTex->GetDC()
//	, 0, 0, iWidth, iHeight
//	, bf);

