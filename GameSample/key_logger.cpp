#include "key_logger.h"

// キーボードの状態を保持する構造体
static Keyboard_State g_PrevState = {};
static Keyboard_State g_TriggerState = {};
static Keyboard_State g_ReleaseState = {};




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
	LPBYTE pr = (LPBYTE)&g_ReleaseState;

	for (int i = 0; i < sizeof(Keyboard_State); i++)
	{
		pt[i] = (pp[i] ^ pn[i]) & pn[i]; // トリガー状態を更新
		pr[i] = (pp[i] ^ pn [i]) & pp[i]; // リリース状態を更新
	}

	g_PrevState = *pState; // 現在の状態を前回の状態として保存
}

bool KeyLogger_IsPressed(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key);
}

bool KeyLogger_IsTrigger(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key, &g_TriggerState);
}

bool KeyLogger_IsReleased(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key, &g_ReleaseState);
}
