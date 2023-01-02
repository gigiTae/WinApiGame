#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CkeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CObject.h"



CCore::CCore()
	:m_hWnd(0)
	,m_ptRseolution{}
	,m_hDC(0)
	,m_hBit(0)
	,m_memDC(0)
	,m_arrBrush{}
	,m_arrPen{}
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // main ������ DC �� ������

	DeleteDC(m_memDC); //  �����쿡�� ���θ��� DC�� Delete 5
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptRseolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0, 0,_ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // window ������Ÿ�Ͽ� �´� rt���� ��ȯ���ش�.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC �� �����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptRseolution.x, m_ptRseolution.y); // ���ο� ��Ʈ���� ������ش�
	m_memDC = CreateCompatibleDC(m_hDC); // ��ο� ��Ʈ�ʿ� �ʿ���  DC�� ����� �ش�.

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit); // �⺻������ 1�ȼ� ¥�� ��Ʈ���� void �� ��ȯ�ȴ�
	DeleteObject(hOldBit); // ��ȯ���� ��Ʈ���� �����Ѵ�.

	// ���� ��� �� �� �귯�� ����
	CreateBrushPen();


	//Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();

	return S_OK;
}


void CCore::progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
 	// =============
	CSceneMgr::GetInst()->update();

	// �浹üũ
	CCollisionMgr::GetInst()->update();



	// ============
	//   Redering
	// ============
	// ȭ�� Clear
	Rectangle(m_memDC, -1, -1, m_ptRseolution.x + 1, m_ptRseolution.y + 1);

	CSceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hDC, 0, 0, m_ptRseolution.x, m_ptRseolution.y
		, m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// ================
	// �̺�Ʈ ����ó��
	// ================
	CEventMgr::GetInst()->update();


}

void CCore::CreateBrushPen()
{

	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

    // red pen	// green pen	// blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
}

