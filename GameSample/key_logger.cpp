#include "key_logger.h"

// �L�[�{�[�h�̏�Ԃ�ێ�����\����
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
		pt[i] = (pp[i] ^ pn[i]) & pn[i]; // �g���K�[��Ԃ��X�V
		pr[i] = (pp[i] ^ pn [i]) & pp[i]; // �����[�X��Ԃ��X�V
	}

	g_PrevState = *pState; // ���݂̏�Ԃ�O��̏�ԂƂ��ĕۑ�
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
