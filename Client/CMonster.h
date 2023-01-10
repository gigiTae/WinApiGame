#pragma once
#include "CObject.h"
class CTextrue;

struct tMonInfo
{
    float   m_fHp;         // ü��
    float   m_fSpeed;      // �ӵ�
    float   m_fRecogRange; // ���� ���� 
    float   m_fAttRange;   // ���� ����
    float   m_fAtt;        // ���ݷ�
};

class AI;

class CMonster :
    public CObject
{
private:
    CTexture* m_pTex;
    tMonInfo  m_tInfo;
    AI*       m_pAI;

public:
    float GetSpeed() { return m_tInfo.m_fSpeed; }
    void  SetSpeed(float _f) { m_tInfo.m_fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }


private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    virtual void OnCollisionEnter(CCollider* _pOther);
   
    CLONE(CMonster);
public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};

