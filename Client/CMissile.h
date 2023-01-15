#pragma once
#include "CObject.h"



class CMissile :
	public CObject
{
private:



public:
	virtual void update();
	virtual void render(HDC _dc);
public:

	CLONE(CMissile);

public:

	CMissile();
	~CMissile();
};

