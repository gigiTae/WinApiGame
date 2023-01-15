#pragma once


// Singleton 매크로
#define SINGLE(type) public:static type* GetInst() {static type mgr; return &mgr;} private:type(); ~type();

#define fDT CTimeMgr::GetInst() -> GetfDT()
#define DT CTimeMgr:: GetInst() -> GetDT()

#define CLONE(type) type* Clone() {return new type(*this);}


#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f

#define TILE_SIZE 64
enum class GROUP_TYPE
{
	DEFALUT,     
	TILE,
	GROUND,
	MONSTER,	 
	PLAYER,		 
	PROJ_PLAYER,  //플레이어 투사체
	PROJ_MONSTER, // 몬스터 투사체

	UI =31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	PLAYGMAE,
	OPTION,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	SKYBLUE,
	DARKBLUE,
	RED,

	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	SKYBLUE,
	DARKBLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	
	END,
};


enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
	END,
};

enum class CollisionDirect // 충돌방향
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NOINFO, // 충돌하지 않음
};
