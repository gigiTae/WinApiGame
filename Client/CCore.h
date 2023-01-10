#pragma once
class CTexture;

class CCore
{
	SINGLE(CCore); 
	//public:static type* GetInst() { static type mgr; return &mgr; } private:type(); ~type();
private:
	HWND m_hWnd;          // ���� ������ �ڵ�
	POINT m_ptRseolution; // ���� ������ �ػ�
	HDC m_hDC;            // ���� ������ Draw �� DC

	CTexture* m_pMemTex;  // ����� ����ó

	// ���� ����ϴ� GDI Object
	HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU m_hMenu; // Tool Scene ������ ���

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC  GetMainDC() { return m_hDC; }

	POINT GetResolution(){ return m_ptRseolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

};
