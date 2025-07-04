/*==============================================================================

   敵の発生制御 [enemy_spawner.h]
														 Author : LCH
														 Date   : 2025/07/02
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

#include "enemy.h" // EnemyTypeIDを使用するために必要
#include <DirectXMath.h>

void EnemySpawner_Initialize();
void EnemySpawner_Finalize();
void EnemySpawner_Update(double elapsed_time);

// 敵の生成
void EnemySpawner_Create(const DirectX::XMFLOAT2& position, EnemyTypeID id, double spawn_time, double spawn_rate, int spawn_count);



#endif // ENEMY_SPAWNER_H
