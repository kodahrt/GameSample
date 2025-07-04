/*==============================================================================

   プレイヤー [player.h]
														 Author : LCH
														 Date   : 2025/06/27
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef PLAYER_H
#define PLAYER_H
#include <DirectXMath.h>	
#include "collision.h"


void Player_Initialize(const DirectX::XMFLOAT2& position);
void Player_Finalize();
void Player_Update(double elapsed_time);
void Player_Draw();

bool Player_IsEnable();
Circle Player_GetCollision(); // プレイヤーの衝突判定用の円を取得
void Player_Destroy(); // プレイヤーを破壊する

#endif // PLAYER_H