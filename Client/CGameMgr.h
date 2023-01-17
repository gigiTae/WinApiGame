#pragma once

class CPlayer;
class CNumberUI;

class CGameMgr
{
	SINGLE(CGameMgr);
private:
	CPlayer* mPlayer;
	CNumberUI* mHpUI;


public:
	void SetmPlayer(CPlayer* _player) { mPlayer = _player; }
	void SetmHpUI(CNumberUI* _hpui) { mHpUI = _hpui; }

	void GameOver();
	void CheckPlayerLife();
	void update();

};

