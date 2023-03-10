#pragma once

class CObject;

class CRigidBody
{
private:
	CObject* m_pOwner;

	Vec2         m_vForce;       // 크기, 방향
	Vec2         m_vAccel;       // 가속도
	Vec2         m_vAccelA;      // 가속도 추가
	Vec2         m_vVelocity;    //속도 (크기 : 속력, 방향)
			    				 
	float        m_fMass;        // 질량
	float        m_fFircCoeff;   // 마찰 계수
	float        m_fMaxSpeed;    // 최대 속력


	// F = M * A;
	// V += A * DT

public:
	void finalupdate();

public:
	void AddForce(Vec2 _vF){m_vForce += _vF;}
	void SetMass(float _fMass) { m_fMass = _fMass;	}
	Vec2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vec2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vec2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(float _Speed) { m_fMaxSpeed = _Speed; }
	void SetAccelAplpha(Vec2 _vAccel) { m_vAccelA = _vAccel; }

private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

