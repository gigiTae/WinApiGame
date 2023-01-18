#pragma once
#include "CScene.h"
class CScene_GameOver :
    public CScene
{
private:
    virtual void Enter();
    virtual void Exit();

public:
    void RetryGame();
    void ExitGame();

public:
    CScene_GameOver();
    ~CScene_GameOver();
};

