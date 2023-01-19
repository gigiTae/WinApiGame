#include "pch.h"
#include "CGameMgr.h"
#include "CPlayer.h"
#include "CNumberUI.h"
#include "CEventMgr.h"
#include "CPathMgr.h"

CGameMgr::CGameMgr()
	:mPlayer(nullptr)
	,mHpUI(nullptr)
	,TimeHundreadNum(nullptr)
	,TimeOneNum(nullptr)
	,TimeTenNum(nullptr)
	,NowTime(0.f)
	,GameOver(false)
{

}

CGameMgr::~CGameMgr()
{

}

void CGameMgr::CheckPlayerLife()
{
	int playerhp =mPlayer->GetPlayerHp();
	mHpUI->SetNumber(playerhp);

	if (0 >= playerhp)
	{
		// ���� �����ϱ�
		wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		strFilePath += L"data\\score.info";
		FILE* pFile = nullptr;

		// bestscore �ҷ�����
		_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
		
		// ó������ ������ ����
		if (nullptr == pFile)
		{
			_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
			assert(pFile);
			int DataTime = (int)NowTime;
			fwrite(&DataTime, sizeof(int), 1, pFile);
			fwrite(&DataTime, sizeof(int), 1, pFile);
			fclose(pFile);
		}
		// ������ �����Ͱ� ����
		else
		{
			int bestscore = 0;
			fread(&bestscore, sizeof(int), 1, pFile);
			fclose(pFile);

			if ((int)NowTime > bestscore)
			{
				bestscore = (int)NowTime;
			}

			int DataTime = (int)NowTime;
			// �̹� ������ �����ϱ�
			_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
			assert(pFile);
			fwrite(&bestscore, sizeof(int), 1, pFile);
			fwrite(&DataTime, sizeof(int), 1, pFile);
			fclose(pFile);
		}

		GameOver= true;
	}

}

void CGameMgr::CheckTime()
{
	int �����ڸ� = (int)NowTime / 100;
	int �����ڸ� = ((int)NowTime-�����ڸ�*100)/10;
	int �����ڸ� = ((int)NowTime - �����ڸ� * 100)%10;

	TimeHundreadNum->SetNumber(�����ڸ�);
	TimeTenNum->SetNumber(�����ڸ�);
	TimeOneNum->SetNumber(�����ڸ�);

}

void CGameMgr::update()
{
	CheckPlayerLife();
	CheckTime();
}
