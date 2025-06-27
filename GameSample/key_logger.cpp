#include "key_logger.h"

// キーボードの状態を保持する構造体
static Keyboard_State g_PrevState = {};
static Keyboard_State g_TriggerState = {};
static Keyboard_State g_ReleasedState = {};




void KeyLogger_Initialize()
{
	Keyboard_Initialize();
}

void KeyLogger_Update()
{
	const Keyboard_State* pState = Keyboard_GetState();
	LPBYTE pn = (LPBYTE)pState;
	LPBYTE pp = (LPBYTE)&g_PrevState;
	LPBYTE pt = (LPBYTE)&g_TriggerState;
	LPBYTE pr = (LPBYTE)&g_ReleasedState;


}

bool KeyLogger_IsPressed(Keyboard_Keys key)
{
	return false;
}

bool KeyLogger_IsTrigger(Keyboard_Keys key)
{
	return false;
}

bool KeyLogger_IsReleased(Keyboard_Keys key)
{
	return false;
}
