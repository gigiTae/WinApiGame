#pragma once
#include "CScene.h"
class CScene_PlayGame :
    public CScene
{
private:
    float PlayTime;

private:
    void EndGame();
 
public:
    virtual void Enter(); // �θ��ʿ��� ��ӹ��� �����Լ��� virtual �� �̿��ؼ� ǥ������
    virtual void Exit();
    virtual void update();

public:

    CScene_PlayGame();
    ~CScene_PlayGame();
};

