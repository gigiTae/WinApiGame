#include "pch.h"
#include "CCamera.h"

#include "CObject.h"

#include "CCore.h"

#include "CTimeMgr.h"
#include "CkeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(2.f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
	, m_pVeilTex(nullptr)
	, m_vLookAt{}
	, m_vCurLookAt{}
	, m_vPreLookAt{}
	, m_vDiff{}
{
}

CCamera::~CCamera()
{

}

void CCamera::init()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::update()
{
	if(m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	CalDiff();

}

void CCamera::render(HDC _dc)
{
	if (m_listCameEffect.empty())
		return;

	// �ð� ������ üũ�ؼ�
	tCamEffect& effect = m_listCameEffect.front();
	effect.fCurTime += fDT;

	float fRatio = 0.f; // ����Ʈ ���� ����
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio >= 1)
	{
		fRatio = 1;
	}
	int iAlpha = 0;
	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{	
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = 255 - (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::BLINGBLING == effect.eEffect)
	{
		iAlpha = rand() % 256;
	}



	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Whidth()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC(), 0, 0
		, (int)m_pVeilTex->Whidth()
		, (int)m_pVeilTex->Height(), bf);

	// ���� �ð��� ����Ʈ �ִ� ���� �ð��� �Ѿ ���
	if (effect.fDuration < effect.fCurTime)
	{
		m_listCameEffect.pop_front();
	}
}

void CCamera::CalDiff()
{
	// ���� LookAt �� ������ ���� ���� �����ؼ� ������ LookAt �� ���Ѵ�.

	m_fAccTime += fDT;
	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPreLookAt;
		if (vLookDir.x == 0 && vLookDir.y == 0)
		{
		}
		else
			vLookDir.Nomalize();
		m_vCurLookAt = m_vPreLookAt + vLookDir * m_fSpeed * fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPreLookAt = m_vCurLookAt;
}
