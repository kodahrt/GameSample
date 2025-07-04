/*==============================================================================

   敵の制御 [enemy.h]
														 Author : LCH
														 Date   : 2025/07/02
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef ENEMY_H
#define ENEMY_H
#include <DirectXMath.h>
#include "collision.h"

static constexpr unsigned int ENEMY_MAX = 256; // 敵の最大数

void Enemy_Initialize();
void Enemy_Finalize();

void Enemy_Update(double elapsed_time);
void Enemy_Draw();

enum EnemyTypeID : int
{
	ENEMY_TYPE_2SHOT, // 敵のタイプ1
	ENEMY_TYPE_NORMAL,     // 敵のタイプ2
	// 他の敵のタイプを追加する場合はここに記述
};

// 敵の生成
void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position);

bool Enemy_IsEnable(int index);
Circle Enemy_GetCollision(int index); // 敵の衝突判定用の円を取得


void Enemy_Destroy(int index);

void Enemy_Damege(int index); // 敵にダメージを与える;






#endif // ENEMY_H