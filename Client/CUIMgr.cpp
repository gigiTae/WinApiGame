#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CkeyMgr.h"

CUIMgr::CUIMgr()
{
}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtmAway = KEY_AWAY(KEY::LBTN);


	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];
		
		if (pUI->IsMouseOn())
		{
			pUI->MouseOn();
			
			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtmAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				// ���ʹ�ư ���� ,���ȴ� üũ�� �ٽ� �����Ѵ�.
				pUI->m_bLbtnDown = false;
			}
		}
		else
		{
			// ���ʹ�ư ���, ���ȴ� üũ�� �ٽ� �����Ѵ�.
			if (bLbtmAway)
			{
				pUI->m_bLbtnDown = false;
			}
		}
	}
}
