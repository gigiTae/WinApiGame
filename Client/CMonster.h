#pragma once
#include "CObject.h"
#include "CTexture.h"

class CMonster :
    public CObject
{
private:
    CTexture* m_pTex;
    Vec2      m_vCenterPos;
    float     m_fSpeed;
    float     m_fMaxDistance;
    int       m_iDir; // 1 -1  

    int       m_HP;

public:
    float GetSpeed() { return m_fSpeed; }
    void  SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    virtual void OnCollisionEnter(CCollider* _pOther);
   
    CLONE(CMonster);
public:
    CMonster();
    ~CMonster();
};
