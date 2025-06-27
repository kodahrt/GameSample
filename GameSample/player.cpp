/*==============================================================================

   �v���C���[ [player.h]
														 Author : LCH
														 Date   : 2025/06/27
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "sprite.h"
#include "texture.h"
#include "key_logger.h"	

static XMFLOAT2 g_PlayerPosition{};
static XMFLOAT2 g_PlayerVelocity{}; // �v���C���[�̑��x
static int g_PlayerTexId = -1; // �v���C���[�̃e�N�X�`��ID;

void Player_Initialize(const XMFLOAT2& position)
{
	// �v���C���[�̏����������������ɋL�q
	// ��: �v���C���[�̈ʒu�A�X�R�A�A���C�t�Ȃǂ̏����l�ݒ�
	g_PlayerPosition = position;
	g_PlayerVelocity = { 0.0f, 0.0f }; // �������x�̓[��
	// �v���C���[�̃e�N�X�`����ǂݍ���
	g_PlayerTexId = Texture_Load(L"kokosozai.png");
}

void Player_Finalize()
{

}

// �v���C���[�̍X�V����
void Player_Update(double elapsed_time)
{
	XMVECTOR position = XMLoadFloat2(&g_PlayerPosition);
	XMVECTOR velocity = XMLoadFloat2(&g_PlayerVelocity);
	
	XMVECTOR direction{};
	// �L�[�{�[�h���͂��擾
	if (KeyLogger_IsPressed(KK_W)) {
		direction += {0.0f, -1.0f}; // �����
	}
	if (KeyLogger_IsPressed(KK_A)) {
		direction += {-1.0f, 0.0f}; // ������
	}
	if (KeyLogger_IsPressed(KK_S)) {
		direction += {0.0f, 1.0f}; // ������
	}
	if (KeyLogger_IsPressed(KK_D)) {
		direction += {1.0f, 0.0f}; // �E����
	}

	direction = XMVector2Normalize(direction); // ���K�����ĕ����x�N�g�����擾

	velocity += direction * 100.0f * elapsed_time; // ���x���X�V

	position += velocity;

	velocity *= 0.95f; // ���C��͋[���邽�߂ɑ��x������
	// ��ʂ̒[�Ŕ��]���鏈�� 
	XMStoreFloat2(&g_PlayerPosition, position);
	XMStoreFloat2(&g_PlayerVelocity, position);


}

void Player_Draw()
{
	Sprite_Draw(g_PlayerTexId,
		g_PlayerPosition.x, g_PlayerPosition.y,
		128.0f, 128.0f,
		0.0f, 0.0f,
		32.0f, 32.0f);
}