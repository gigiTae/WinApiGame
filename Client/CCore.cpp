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
#include "CUIMgr.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "resource.h"


CCore::CCore()
	:m_hWnd(0)
	,m_ptRseolution{}
	,m_hDC(0)
	,m_arrBrush{}
	,m_arrPen{}
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // main ������ DC �� ������


	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	for (int i = (UINT)BRUSH_TYPE::SKYBLUE; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}

	DestroyMenu(m_hMenu);
}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptRseolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// �޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));


	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� �ؽ�ó ������ �����
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptRseolution.x, (UINT)m_ptRseolution.y);

	// ���� ��� �� �� �귯�� ����
	CreateBrushPen();

	

	//Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
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

	// UI �̺�Ʈ üũ
	CUIMgr::GetInst()->update();


	// ============
	//   Redering
	// ============
	// ȭ�� Clear
	Clear();


	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptRseolution.x, m_ptRseolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// ================
	// �̺�Ʈ ����ó��
	// ================
	CEventMgr::GetInst()->update();


}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::SKYBLUE);

	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptRseolution.x + 1, m_ptRseolution.y + 1);
}

void CCore::CreateBrushPen()
{

	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::SKYBLUE] = CreateSolidBrush(RGB(203, 219, 252));
	m_arrBrush[(UINT)BRUSH_TYPE::DARKBLUE] = CreateSolidBrush(RGB(63, 63, 116));
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));


    // red pen	// green pen	// blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::SKYBLUE] = CreatePen(PS_SOLID, 1, RGB(203, 219, 252));
	m_arrPen[(UINT)PEN_TYPE::DARKBLUE] = CreatePen(PS_SOLID, 1, RGB(63, 63, 116));
}

void CCore::DockMenu()
{
	SetMenu(m_hWnd, m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0, 0,(long)_vResolution.x, (long)_vResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu); // window ������Ÿ�Ͽ� �´� rt���� ��ȯ���ش�.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}

