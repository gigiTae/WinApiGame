#pragma once
#include "CUI.h"
class CFixedUI :
    public CUI
{

private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    CLONE(CFixedUI);
public:
    CFixedUI();
    ~CFixedUI();

};

