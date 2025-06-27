/*==============================================================================

   ÉvÉåÉCÉÑÅ[ [player.h]
														 Author : LCH
														 Date   : 2025/06/27
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef PLAYER_H
#define PLAYER_H
#include <DirectXMath.h>	


void Player_Initialize(const DirectX::XMFLOAT2& position);
void Player_Finalize();
void Player_Update(double elapsed_time);
void Player_Draw();

#endif // PLAYER_H