/*==============================================================================

   Sprite header[sprite.h]
														 Author : LCH
														 Date   : 2025/06/12
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef SPRITE_H
#define SPRITE_H

#include <d3d11.h>
#include <DirectXMath.h>

void Sprite_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Sprite_Finalize(void);


void Sprite_Begin();

//テクスチャ全表示
void Sprite_Draw(int texid, float dx, float dy, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

//can change texture output size 
void Sprite_Draw(int texid, float dx, float dy, float dw, float dh, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

//UV cut
void Sprite_Draw(int texid, float dx, float dy, int px, int py, int pw, int ph, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

//UV cut that can change output size
void Sprite_Draw(int texid, float dx, float dy, float dw, float dh, int px, int py, int pw, int ph, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

//UV cut that can change output size (Rotate 回転)
void Sprite_Draw(int texid, float dx, float dy, float dw, float dh, int px, int py, int pw, int ph, float angle, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

#endif // SPRITE_H
