/*==============================================================================

   �v���C���[ [player.cpp]
														 Author : LCH
														 Date   : 2025/06/27
--------------------------------------------------------------------------------

==============================================================================*/

#include "bullet.h"
#include <DirectXMath.h>
#include "direct3d.h"
#include "sprite.h"
#include "texture.h"
using namespace DirectX;

struct Bullet
{
	XMFLOAT2 position{}; // �e�̈ʒu
	XMFLOAT2 velocity{}; // �e�̑��x
	bool isEnabled; // �e���L�����ǂ���
	double life_time; // �e�̃��C�t�^�C��
};

// BULLET MAX
static constexpr unsigned int BULLET_MAX = 1024; // �e�̍ő吔
static Bullet g_Bullets[BULLET_MAX]{}; // �e�̔z��
static int g_BulletTexId = -1;

void Bullet_Initialize()
{
	// �e�̏����������������ɋL�q
	// ��: �e�̈ʒu�A���x�A���C�t�Ȃǂ̏����l�ݒ�
	// g_BulletPosition = position;
	// g_BulletVelocity = { 0.0f, 0.0f }; // �������x�̓[��
	// g_BulletTexId = Texture_Load(L"bullet.png"); // �e�̃e�N�X�`����ǂݍ���
	for (Bullet& b : g_Bullets) {
		b.isEnabled = false; // ���������͑S�Ė���
	}
	g_BulletTexId = Texture_Load(L"bullet.png"); // �e�̃e�N�X�`����ǂݍ���

}

void Bullet_Finalize()
{
	// �e�̏I�������������ɋL�q
	// ��: �������̉���A���\�[�X�̃N���[���A�b�v�Ȃ�
	// Texture_Release(g_BulletTexId); // �e�̃e�N�X�`�������
}

void Bullet_Update(double elapsed_time)
{
	// �e�̍X�V�����������ɋL�q
	// ��: �e�̈ʒu�A���x�A���C�t�̍X�V�Ȃ�
	// XMVECTOR position = XMLoadFloat2(&g_BulletPosition);
	// XMVECTOR velocity = XMLoadFloat2(&g_BulletVelocity);
	// position += velocity * static_cast<float>(elapsed_time);
	// XMStoreFloat2(&g_BulletPosition, position);

	for (Bullet& b : g_Bullets) {
		if (!b.isEnabled) continue; // �e�������ȏꍇ�̓X�L�b�v
		// �e�̈ʒu���X�V
		XMVECTOR position = XMLoadFloat2(&b.position);
		XMVECTOR velocity = XMLoadFloat2(&b.velocity);

		position += velocity * elapsed_time;

		// �e�̈ʒu��ۑ�
		XMStoreFloat2(&b.position, position);
		XMStoreFloat2(&b.velocity, velocity);
		// ���C�t�^�C�����X�V
		b.life_time += elapsed_time; // ���C�t�^�C��������

		if (b.life_time > 5.0f) {
			b.isEnabled = false; // ���C�t�^�C����0�ȉ��ɂȂ�����e�𖳌���
		}

		// ��ʊO�ɏo����e�𖳌���
		if (b.position.y < 0.0f || b.position.y > Direct3D_GetBackBufferHeight() ||
			b.position.x < 0.0f || b.position.x > Direct3D_GetBackBufferWidth()) {
			b.isEnabled = false; 
		}
	}

}

void Bullet_Draw()
{
	// �e�̕`�揈���������ɋL�q
	// ��: �e�̈ʒu�Ƀe�N�X�`����`�悷��
	// Sprite_Draw(g_BulletTexId, g_BulletPosition.x, g_BulletPosition.y, 32.0f, 32.0f);
	for (const Bullet& b : g_Bullets) {
		if (!b.isEnabled) continue; // �e�������ȏꍇ�̓X�L�b�v
		Sprite_Draw(g_BulletTexId, b.position.x, b.position.y, 32.0f, 32.0f);
	}
}


void Bullet_Create(const DirectX::XMFLOAT2& position)  
{  
    for (Bullet& b : g_Bullets) {  
        if (!b.isEnabled) { // �e�������ȏꍇ�̓X�L�b�v���Ȃ�  
            // �󂫗̈����������A���̒e��L�������ď�����  
            b.isEnabled = true; // �e��L����  
            b.life_time = 0.0; // ���C�t�^�C����ݒ�  
            b.position = position; // �e�̏����ʒu��ݒ�  
            b.velocity = DirectX::XMFLOAT2(200.0f, 0.0f); // ������ɔ��˂��鑬�x��ݒ�  
            break;  
        }  
    }  
}
