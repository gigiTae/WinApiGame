#pragma once
#include "CScene.h"
class CScene_PlayGame :
    public CScene
{

private:

    void EndGame();

public:
    virtual void Enter(); // �θ��ʿ��� ��ӹ��� �����Լ��� virtual �� �̿��ؼ� ǥ������
    virtual void Exit();

public:

    CScene_PlayGame();
    ~CScene_PlayGame();
};

