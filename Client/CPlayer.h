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

    float          m_MissileTimer;
    int            m_CanMoveW;
    int            m_CanMoveA;
    int            m_CanMoveS;
    int            m_CanMoveD;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

private:
    virtual void DirLeftCollision();
    virtual void DirRightCollision();
    virtual void DirUpCollision();
    virtual void DirDownCollision();

    void CreateMissile();

    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();

};

