
#include "game.h"
#include "player.h"
#include "bullet.h"

void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f }); // �v���C���[�̏����ʒu��ݒ�
	// ���̏���������������΂����ɒǉ�	Player_Initialize();
	Bullet_Initialize();
}

void Game_Finalize()
{
	Player_Finalize(); // �v���C���[�̏I���������Ăяo��
	Bullet_Finalize(); // �e�̏I���������Ăяo��
	// ���̏I������������΂����ɒǉ�
	// ��: �G�̏I���A�X�R�A�̕ۑ��Ȃ�
}

void Game_Update(double elapsed_time)
{
	Player_Update(elapsed_time); // �v���C���[�̍X�V�������Ăяo��
	// ���̍X�V����������΂����ɒǉ�
	// ��: �G�̍X�V�A�X�R�A�̍X�V�Ȃ�
	Bullet_Update(elapsed_time); // �e�̍X�V�������Ăяo��
}

void Game_Draw()
{
	
	// �Q�[���̕`�揈���������ɋL�q
	Bullet_Draw(); 
	Player_Draw();
}
