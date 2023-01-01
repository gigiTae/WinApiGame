#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_IICurCount;
	LARGE_INTEGER m_IIPrevCount;
	LARGE_INTEGER m_IIFrequency;

	double        m_dDT; // ������ ���� �ð� ��
	double        m_dAcc; // 1�� üũ�� ���� ���� �ð�
	UINT          m_iCallCount; // �Լ� ȣ�� Ƚ�� üũ
	UINT          m_iFPS; // �ʴ� ȣ��Ƚ��

	// FPS 
	// 1. �����Ӵ� �ð� (Delta Time)

public:
	void init();
	void update();
	void render();
	
public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }

};
