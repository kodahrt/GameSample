/*==============================================================================

   �G�̐��� [enemy.h]
														 Author : LCH
														 Date   : 2025/07/02
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef ENEMY_H
#define ENEMY_H
#include <DirectXMath.h>
#include "collision.h"

static constexpr unsigned int ENEMY_MAX = 256; // �G�̍ő吔

void Enemy_Initialize();
void Enemy_Finalize();

void Enemy_Update(double elapsed_time);
void Enemy_Draw();

enum EnemyTypeID : int
{
	ENEMY_TYPE_2SHOT, // �G�̃^�C�v1
	ENEMY_TYPE_NORMAL,     // �G�̃^�C�v2
	// ���̓G�̃^�C�v��ǉ�����ꍇ�͂����ɋL�q
};

// �G�̐���
void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position);

bool Enemy_IsEnable(int index);
Circle Enemy_GetCollision(int index); // �G�̏Փ˔���p�̉~���擾


void Enemy_Destroy(int index);

void Enemy_Damege(int index); // �G�Ƀ_���[�W��^����;






#endif // ENEMY_H