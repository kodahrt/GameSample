/*==============================================================================

		�e�N�X�`���Ǘ�[texture.h]
														 Author : LCH
														 Date   : 2025/06/13

--------------------------------------------------------------------------------

==============================================================================*/
#ifndef TEXTURE_H
#define TEXTURE_H
#include <d3d11.h>

void Texture_Initialize(ID3D11Device* pDevice,ID3D11DeviceContext* pContext);
void Texture_Finalize(void);

//�e�N�X�`���摜�̓ǂݍ���
// 
//�߂�l:�Ǘ��ԍ��B�ǂݍ��߂Ȃ������ꍇ -1�B
//


int Texture_Load(const wchar_t*pFilename);

void Texture_AllRelease();

void Texture_SetTexture(int texid);
unsigned int Texture_Width(int texid);
unsigned int Texture_Height(int texid);

#endif //TEXTURE_H
