#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CkeyMgr.h"
#include "CTimeMgr.h"
#include "CEventMgr.h"

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
	,m_CanMoveW(0)
	,m_CanMoveA(0)
	,m_CanMoveS(0)
	,m_CanMoveD(0)
	, m_Hp(3)
{
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"Player1Tex", L"texture\\c1.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 18.f));
	GetCollider()->SetScale(Vec2(24.f, 28.f));
	
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
	if (GetRigidBody()->GetVelocity() == Vec2(0.f, 0.f) && KEY_NONE(KEY::S) && KEY_NONE(KEY::D) && KEY_NONE(KEY::A) && KEY_NONE(KEY::W))
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}

}

void CPlayer::update_move()
{

	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::W) && m_CanMoveW == 0)
	{
		pRigid->AddForce(Vec2(0.f, -1500.f));
	}
	if (KEY_HOLD(KEY::S) && m_CanMoveS == 0)
	{
		pRigid->AddForce(Vec2(0.f, 1500.f));
	}
	if (KEY_HOLD(KEY::A) && m_CanMoveA == 0)
	{
		pRigid->AddForce(Vec2(-1500.f, 0.f));
	}
	if (KEY_HOLD(KEY::D) && m_CanMoveD == 0)
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




void CPlayer::OnCollisionEnter(CCollider* _pOther, CollisionDirect _direct)
{
	wstring name = _pOther->GetObj()->GetName();
	if (name == L"Tile")
	{
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		if (_direct == CollisionDirect::LEFT)
		{
			++m_CanMoveA;
			Vec2 vPos = GetPos();
			vPos.x += 1.f;
			SetPos(vPos);
		}
		if (_direct == CollisionDirect::RIGHT)
		{
			++m_CanMoveD;
			Vec2 vPos = GetPos();
			vPos.x -= 1.f;
			SetPos(vPos);
		}
		if (_direct == CollisionDirect::DOWN)
		{
			++m_CanMoveS;
			Vec2 vPos = GetPos();
			vPos.y -= 1.f;
			SetPos(vPos);
		}
		if (_direct == CollisionDirect::UP)
		{
			++m_CanMoveW;
			Vec2 vPos = GetPos();
			vPos.y += 1.f;
			SetPos(vPos);
		}
	}
	if (name == L"Missile")
	{
		CMissile* missile = (CMissile*)_pOther->GetObj();
		float CreateTime = missile->GetAfterCreate();
		if (CreateTime > 2.f)
		{
		--m_Hp;
		tEvent eve = {};
		eve.eEven = EVENT_TYPE::DELETE_OBJECT;
		eve.lParam = (DWORD_PTR)_pOther->GetObj();
		CEventMgr::GetInst()->AddEvent(eve);
		}
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther, CollisionDirect _direct)
{
	wstring name = _pOther->GetObj()->GetName();
	if (name == L"Tile")
	{
		if (_direct == CollisionDirect::LEFT)
			--m_CanMoveA;
		if (_direct == CollisionDirect::RIGHT)
			--m_CanMoveD;
		if (_direct == CollisionDirect::DOWN)
			--m_CanMoveS;
		if (_direct == CollisionDirect::UP)
			--m_CanMoveW;
	}
}

void CPlayer::CreateMissile()
{
	Vec2 PlayerPos =GetPos();
	PlayerPos += Vec2(0.f, -5.f);
	CMissile* NewMissile = new CMissile;
	NewMissile->SetName(L"Missile");
	NewMissile->SetPos(PlayerPos);
	NewMissile->SetScale(Vec2(20.f, 20.f));
	NewMissile->CreateRigidBody();
	
	//난수 초기화
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dir(-200, 200);
	Vec2 Direct = Vec2((float)dir(gen), -100.f);
	Direct.Nomalize();

	if (PlayerPos.y < 75.f)
		Direct.y = -Direct.y;

	NewMissile->SetvDirect(Direct);
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)NewMissile;
	evn.wParam = (DWORD_PTR)GROUP_TYPE::PROJ_PLAYER;
	CEventMgr::GetInst()->AddEvent(evn);
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

