#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_IICurCount{}
	, m_IIPrevCount{}
	, m_IIFrequency{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_dAcc(0.)
	, m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_IIPrevCount);

	// �ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_IIFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_IICurCount);

	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_IICurCount.QuadPart - m_IIPrevCount.QuadPart) / (double)m_IIFrequency.QuadPart;

	// ���� ī��Ʈ ���� ���簪���� ����(�������� ����� ���ؼ�)
	m_IIPrevCount = m_IICurCount;


#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif

}

void CTimeMgr::render()
{
	++m_iCallCount;
	m_dAcc += m_dDT; // DT ���� 

	if (m_dAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0.;
		++m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
