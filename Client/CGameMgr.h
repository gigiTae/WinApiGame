#pragma once

class CPlayer;
class CNumberUI;

class CGameMgr
{
	SINGLE(CGameMgr);
private:
	bool GameOver; 
	// 플레이어 HP UI
	CPlayer* mPlayer;
	CNumberUI* mHpUI;

	float NowTime;
	// 시간 UI
	CNumberUI* TimeHundreadNum;
	CNumberUI* TimeTenNum;
	CNumberUI* TimeOneNum;
public:
	bool IsGameOver() { return GameOver; }
	void SetGameOver(bool _tf) { GameOver = _tf; }

	void SetmPlayer(CPlayer* _player) { mPlayer = _player; }
	void SetmHpUI(CNumberUI* _hpui) { mHpUI = _hpui; }
	void CheckPlayerLife();

public:
	void SetHundreadNum(CNumberUI* _ui) { TimeHundreadNum = _ui; }
	void SetTneNum(CNumberUI* _ui) { TimeTenNum = _ui; }
	void SetOneNum(CNumberUI* _ui) { TimeOneNum = _ui; }

	void CheckTime();

	void SetNowTime(float _time) { NowTime = _time; }


public:
	void update();

};

