#pragma once
#include "CUI.h"

class CTexture;

class CNumberUI :
    public CUI
{
private:
    int m_Number;
    CTexture* m_UITex;
public:
    int GetNumber() { return m_Number; }
    void SetNumber(int num) { m_Number = num; }
    void AddNumber() { ++m_Number; }

public:
    virtual void render(HDC _dc);

private:


    CLONE(CNumberUI);
public:
    CNumberUI();
    ~CNumberUI();
};

