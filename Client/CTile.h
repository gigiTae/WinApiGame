#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture* m_pTileTex;
    int       m_iImgIdx;

public:
    int GetImgIdx() { return m_iImgIdx; }
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;
    }

    void SetImgIdx(int _imgidx)
    {
        m_iImgIdx = _imgidx;
    }
private:
    virtual void update();
    virtual void render(HDC _dc);
    

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);
    
    CLONE(CTile);
public:
    CTile();
    ~CTile();

};

