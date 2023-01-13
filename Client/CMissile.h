#pragma once
#include "CObject.h"



class CMissile :
	public CObject
{
private:



public:
	virtual void update() = 0;

public:

	//CLONE(CMissile);

public:

	CMissile();
	~CMissile();
};

