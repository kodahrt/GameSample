// ==========================================================================================================

// Effect.cpp

																			//	LEE CHEE HOW

// /*========================================================================================================
#include "effect.h"
#include <DirectXMath.h>
#include "direct3d.h"
#include "sprite_anim.h"
#include "texture.h"
using namespace DirectX;
// Effect�̍\����
struct Effect
{
	XMFLOAT2 position{}; // �e�̈ʒu
//	XMFLOAT2 velocity{}; // �e�̑��x
	int sprite_anim_id; // �X�v���C�g�A�j���[�V����ID
	bool isEnabled; // �e���L�����ǂ���
//	double life_time; // �e�̃��C�t�^�C��
//	Circle collision; // �e�̏Փ˔���p�̉~
};

static constexpr int EFFECT_MAX = 256; // �e�̍ő吔
static Effect g_Effects[EFFECT_MAX]{}; // �e�̔z��
static int g_EffectTexId = -1; // �e�̃e�N�X�`��ID
static int g_AnimPatternId = -1; // �X�v���C�g�A�j���[�V�����̃p�^�[��ID

void Effect_Initialize()
{
	for (Effect& e : g_Effects) {
		e.isEnabled = false; // ���������͑S�Ė���
	}

	g_EffectTexId = Texture_Load(L"Explosion.png"); // �e�̃e�N�X�`����ǂݍ���
	g_AnimPatternId = SpriteAnim_RegisterPattern(
		g_EffectTexId, 16, 4, // �p�^�[���̉��Əc�̐�
		0.05, // 1�t���[��������̕b��
		{ 256, 256 }, // �p�^�[���̃T�C�Y
		{ 0, 0 }, // �J�n�ʒu
		false // ���[�v���邩�ǂ���
	);
}

void Effect_Finalize()
{
}

void Effect_Update(double elapsed_time)
{
	for (Effect& e : g_Effects) {
		if (!e.isEnabled) continue;

		if (SpriteAnim_IsStopped(e.sprite_anim_id)) {
			SpriteAnim_DestroyPlayer(e.sprite_anim_id); // �X�v���C�g�A�j���[�V������j��
			e.isEnabled = false; // �X�v���C�g�A�j���[�V��������~������e�𖳌���
		}
	}
}

void Effect_Draw()
{
	for (const Effect& e : g_Effects) {
		if (!e.isEnabled) continue; // �e�������ȏꍇ�̓X�L�b�v
		SpriteAnim_Draw(e.sprite_anim_id, e.position.x, e.position.y, 64.0f, 64.0f);
	}
}

void Effect_Create(const DirectX::XMFLOAT2& position, int typeId)
{
	for (Effect& e : g_Effects) {
		if (e.isEnabled) continue;  // �e�������ȏꍇ�̓X�L�b�v���Ȃ�  
			// �󂫗̈����������A���̒e��L�������ď�����  
		e.isEnabled = true; // �e��L����
		e.position = position; // �e�̏����ʒu��ݒ�
		e.sprite_anim_id = SpriteAnim_CreatePlayer(typeId); // �X�v���C�g�A�j���[�V�������쐬
		break;
	}
}
