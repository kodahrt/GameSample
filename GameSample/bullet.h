/*==============================================================================

   íeÇÃêßå‰ [bullet.h]
														 Author : LCH
														 Date   : 2025/07/01
--------------------------------------------------------------------------------

==============================================================================*/

#ifndef BULLET_H
#define BULLET_H

#include <DirectXMath.h>

void Bullet_Initialize();
void Bullet_Finalize();
void Bullet_Update(double elapsed_time);
void Bullet_Draw();
// íeÇÃê∂ê¨
void Bullet_Create(const DirectX::XMFLOAT2& position);


#endif // BULLET_H