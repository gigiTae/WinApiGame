#pragma once

class CUI;


class CUIMgr
{
	SINGLE(CUIMgr);

private:



public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI); // �θ� UI������ ������ Ÿ���õ� UI�� ã�Ƽ� ��ȯ�Ѵ�.

};

