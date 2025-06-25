#ifndef SHADER_H
/*==============================================================================

   �V�F�[�_�[ [shader.h]
														 Author : LCH
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/

#define	SHADER_H

#include <d3d11.h>
#include <DirectXMath.h>

bool Shader_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Shader_Finalize();

void Shader_SetProjectionMatrix(const DirectX::XMMATRIX& matrix);
void Shader_SetWorldMatrix(const DirectX::XMMATRIX& matrix);

void Shader_Begin();

#endif // SHADER_H
