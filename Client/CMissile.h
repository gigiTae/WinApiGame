#pragma once
#include "CObject.h"



class CMissile :
	public CObject
{
private:
	Vec2 vDirect;
	float AfterCreate; // ������ �ð�


public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	float GetAfterCreate() { return AfterCreate; }
	void  SetvDirect(Vec2 vec) { vDirect.x = vec.x; vDirect.y = vec.y; }
	virtual void OnCollisionEnter(CCollider* _pOther, CollisionDirect _direct);
public:

	CLONE(CMissile);

public:

	CMissile();
	~CMissile();
};

