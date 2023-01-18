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
    virtual void Enter(); // 부모쪽에서 상속받은 가상함수르 virtual 을 이용해서 표시하자
    virtual void Exit();
    virtual void update();

public:

    CScene_PlayGame();
    ~CScene_PlayGame();
};

