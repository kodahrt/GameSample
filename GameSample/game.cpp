
#include "game.h"
#include "player.h"

void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f }); // �v���C���[�̏����ʒu��ݒ�
	// ���̏���������������΂����ɒǉ�	Player_Initialize();
}

void Game_Finalize()
{
}

void Game_Update(double elapsed_time)
{
	Player_Update(elapsed_time); // �v���C���[�̍X�V�������Ăяo��
	// ���̍X�V����������΂����ɒǉ�
	// ��: �G�̍X�V�A�X�R�A�̍X�V�Ȃ�
}

void Game_Draw()
{
	Player_Draw();
}
