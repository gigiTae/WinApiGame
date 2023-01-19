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
		// 파일 저장하기
		wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
		strFilePath += L"data\\score.info";
		FILE* pFile = nullptr;

		// bestscore 불러오기
		_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
		
		// 처음으로 데이터 저장
		if (nullptr == pFile)
		{
			_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
			assert(pFile);
			int DataTime = (int)NowTime;
			fwrite(&DataTime, sizeof(int), 1, pFile);
			fwrite(&DataTime, sizeof(int), 1, pFile);
			fclose(pFile);
		}
		// 기존의 데이터가 있음
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
			// 이번 데이터 저장하기
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
	int 백의자리 = (int)NowTime / 100;
	int 십의자리 = ((int)NowTime-백의자리*100)/10;
	int 일의자리 = ((int)NowTime - 백의자리 * 100)%10;

	TimeHundreadNum->SetNumber(백의자리);
	TimeTenNum->SetNumber(십의자리);
	TimeOneNum->SetNumber(일의자리);

}

void CGameMgr::update()
{
	CheckPlayerLife();
	CheckTime();
}
