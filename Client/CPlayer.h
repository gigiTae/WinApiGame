#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    JUMP,
    DEAD,
};

enum class PLAYER_ATTACK_STATE
{
    NOMAL_ATT_1,
    NOMAL_ATT_2,
    NOMAL_ATT_3,

    SKILL_ATT_1,
    // ..
};


enum class KEY;
class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture*   m_pTex;

    PLAYER_STATE   m_eCurState;
    PLAYER_STATE   m_ePrevState;
    KEY            m_iDir;
    int            m_Hp;

    float          m_MissileTimer;
    int            m_CanMoveW;
    int            m_CanMoveA;
    int            m_CanMoveS;
    int            m_CanMoveD;

public:
    virtual void update();
    virtual void render(HDC _dc);
    int GetPlayerHp() { return m_Hp; }
    void SetPlayerHp(int _hp) { m_Hp = _hp; }
private:
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

private:
    virtual void OnCollisionEnter(CCollider* _pOther, CollisionDirect _direct);
    virtual void OnCollisionExit(CCollider* _pOther, CollisionDirect _direct);

    void CreateMissile();

    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();

};

