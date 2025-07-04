
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy_spawner.h"
#include "effect.h"

static double g_Time = 0.0; // �Ō�Ɏ��s��������
static double g_CreateTime = 0.0;

void hitJudgmentBulletVSEnemy(); // �e�ƓG�̏Փ˔�����s���֐��̐錾
void hitJudgmentPlayertVSEnemy(); // �v���C���[�ƓG�̏Փ˔�����s���֐��̐錾

void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f }); // �v���C���[�̏����ʒu��ݒ�
	// ���̏���������������΂����ɒǉ�	Player_Initialize();
	Bullet_Initialize(); // �e�̏������������Ăяo��
	Enemy_Initialize(); // �G�̏������������Ăяo��
	EnemySpawner_Initialize(); // �G�̔�������̏������������Ăяo��

	// �G�̐�����
	EnemySpawner_Create({ 1600.0f, 450 - 64 }, ENEMY_TYPE_2SHOT, 3.0f ,	0.5, 5); // �G�̐�����ݒ�
}

void Game_Finalize()
{
	Player_Finalize(); // �v���C���[�̏I���������Ăяo��
	Bullet_Finalize(); // �e�̏I���������Ăяo��
	// ���̏I������������΂����ɒǉ�
	// ��: �G�̏I���A�X�R�A�̕ۑ��Ȃ�
	Enemy_Finalize(); // �G�̏I���������Ăяo��
	EnemySpawner_Finalize(); // �G�̔�������̏I���������Ăяo��
}

void Game_Update(double elapsed_time)
{
	EnemySpawner_Update(elapsed_time); // �G�̔�������̍X�V�������Ăяo��
	Player_Update(elapsed_time); // �v���C���[�̍X�V�������Ăяo��
	// ���̍X�V����������΂����ɒǉ�
	// ��: �G�̍X�V�A�X�R�A�̍X�V�Ȃ�
	Bullet_Update(elapsed_time); // �e�̍X�V�������Ăяo��
	Enemy_Update(elapsed_time); // �G�̍X�V�������Ăяo��

	hitJudgmentBulletVSEnemy(); // �e�ƓG�̏Փ˔�����s��
	hitJudgmentPlayertVSEnemy(); // �v���C���[�ƓG�̏Փ˔�����s��

	Effect_Update(elapsed_time); // �G�t�F�N�g�̍X�V�������Ăяo��
}

void Game_Draw()
{
	// �Q�[���̕`�揈���������ɋL�q
	Enemy_Draw();
	Bullet_Draw(); 
	Player_Draw();
	Effect_Draw(); // �G�t�F�N�g�̕`�揈�����Ăяo��
}

void hitJudgmentBulletVSEnemy()
{
	for (int bi = 0; bi < BULLET_MAX; bi++) {   
		if (!Bullet_IsEnable(bi)) continue; // �e�������ȏꍇ�̓X�L�b�v
		Circle bulletCollision = Bullet_GetCollision(bi); // �e�̏Փ˔���p�̉~���擾
		for (int ei = 0; ei < ENEMY_MAX; ei++) {
			if (!Enemy_IsEnable(ei)) continue; // �G�������ȏꍇ�̓X�L�b�v
			Circle enemyCollision = Enemy_GetCollision(ei); // �G�̏Փ˔���p�̉~���擾
			if (Collision_IsOverlapCircle(bulletCollision, enemyCollision)) {
				// �e�ƓG���Փ˂����ꍇ�̏���
				Bullet_Destroy(bi); // �e��j                                                                                                              ��
				Enemy_Damege(ei); // �G�Ƀ_���[�W��^����
			}
		}
	}
}

void hitJudgmentPlayertVSEnemy()
{		
	if (!Player_IsEnable()) return; // �v���C���[�������ȏꍇ�̓X�L�b�v
	for (int ei = 0; ei < ENEMY_MAX; ei++) {
		if (!Enemy_IsEnable(ei)) continue; // �G�������ȏꍇ�̓X�L�b�v
		Circle enemyCollision = Enemy_GetCollision(ei); // �G�̏Փ˔���p�̉~���擾
		if (Collision_IsOverlapCircle(Player_GetCollision(), enemyCollision)) {
			// �v���C���[�ƓG���Փ˂����ꍇ�̏���
			Player_Destroy(); // �v���C���[��j��
			Enemy_Destroy(ei); // �G��j��
		}
	}
    
}
