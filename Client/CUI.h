#pragma once
#include "CObject.h"

class CTexture;

class CUI :
    public CObject
{
    //;
private:
    vector<CUI*>   m_vecChildUI;
    CUI*           m_ParentUI;
    Vec2           m_vFinalPos;
    CTexture*      m_pTex;

    bool           m_bCamAffected; // UI ī�޶� ������ �޴� ����
    bool           m_bMouseOn;     // UI ���� ���콺�� �ִ���
    bool           m_bLbtnDown;    // UI �� ���ʹ�ư�� �������� �ִ��� 


public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_ParentUI; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool ISLbtnDown() { return m_bLbtnDown; }

    CTexture* GetTexture() { return m_pTex; }
    void SetTexture(CTexture* _tex) { m_pTex = _tex; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_ParentUI = this; }
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

    
protected:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();
public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

    virtual CUI* Clone() = 0;

public:

    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};

