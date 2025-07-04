/*========================================================================================


    �G�̐��� (Enemy CPP)												LCH
                                                            DATE:02/07/2005

------------------------------------------------------------------------------------------

=========================================================================================*/
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
using namespace DirectX;
#include "collision.h"

struct EnemyType
{
	int texId; // �G�̃e�N�X�`��ID
	int tx, ty, tw, th; // �e�N�X�`����UV���W�ƃT�C�Y
	XMFLOAT2 velocity; // �G�̑��x
	Circle collision; // �G�̏Փ˔���p�̉~

	// status
	int hp; // �G�̍ő�HP
};

struct Enemy
{
	int typeId; // �G�̃^�C�vID
	XMFLOAT2 position; // �G�̈ʒu
	XMFLOAT2 velocity; // �G�̑��x
	float offsetY; // �G��Y�I�t�Z�b�g�i�A�j���[�V�����p�Ȃǁj
	double lifeTime; // �G�̃��C�t�^�C��
	bool isEnabled; // �G���L�����ǂ���

	Circle collision; // �G�̏Փ˔���p�̉~

	int hp; // �G��HP
};


static Enemy g_Enemies[ENEMY_MAX]{}; // �G�̔z��
static int g_EnemyTexId = -1; // �G�̃e�N�X�`��ID
static constexpr float ENEMY_WIDTH = 32.0f; // �G�̕�
static constexpr float ENEMY_HEIGHT = 32.0f; // �G�̍���
static EnemyType g_EnemyTypes[]{
	{ -1, 32, 32, 10 }, // �G�̃^�C�v1
	{ -1, 32, 32, 2 } // �G�̃^�C�v2
	// ���̓G�̃^�C�v��ǉ�����ꍇ�͂����ɋL�q
};

void Enemy_Initialize()  
{  
   for (Enemy& e : g_Enemies) {  
       e.isEnabled = false; // ���������͑S�Ė���  
   }  
   //g_EnemyTypes[0].texId = Texture_Load(L"enemy.png"); // �e�̃e�N�X�`����ǂݍ���  
   //g_EnemyTypes[1].texId = Texture_Load(L"enemy.png"); // �e�̃e�N�X�`����ǂݍ���  
   g_EnemyTexId = Texture_Load(L"enemy.png"); // �G�̃e�N�X�`����ǂݍ���
}

void Enemy_Finalize()
{

}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& e : g_Enemies) {
		if (!e.isEnabled) continue; // �e�������ȏꍇ�̓X�L�b�v

		switch (e.typeId)
		{
		case ENEMY_TYPE_2SHOT:
			// 2WAY�e�̏���
			e.position.x += e.velocity.x * elapsed_time;
			e.position.y = e.offsetY * sinf(e.lifeTime) * 100.0f; // Y���̃I�t�Z�b�g���T�C���g�ōX�V
			break;
		case ENEMY_TYPE_NORMAL:
			XMVECTOR position = XMLoadFloat2(&e.position);
			XMVECTOR velocity = XMLoadFloat2(&e.velocity);
			// �e�̈ʒu��ۑ�
			XMStoreFloat2(&e.position, position);
			XMStoreFloat2(&e.velocity, velocity);
			// �ʏ�e�̏���
			position += velocity * static_cast<float>(elapsed_time); // �e�̈ʒu���X�V
			break;
		}



		e.lifeTime += elapsed_time; // ���C�t�^�C�����X�V
		
		if (e.position.x < 0.0f ) {
			e.isEnabled = false; // ��ʊO�ɏo���疳����
		}

	}
}

void Enemy_Draw()
{
	for (Enemy& e : g_Enemies) {
		if (!e.isEnabled) continue; // �e�������ȏꍇ�̓X�L�b�v
		Sprite_Draw(g_EnemyTexId, e.position.x, e.position.y, ENEMY_WIDTH, ENEMY_HEIGHT);
	};
}

void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position)
{
	for (Enemy& e : g_Enemies) {
		if (!e.isEnabled) {
			e.position = position; // �G�̈ʒu��ݒ�
			e.typeId = id; // �G�̃^�C�v��ݒ�
			e.lifeTime = 0.0; // �G�̃��C�t�^�C����������
			e.offsetY = position.y; // Y�I�t�Z�b�g��������
			e.velocity = { -200.0f, 0.0f }; // �������Ɉړ�
			e.isEnabled = true; // �G��L����
			e.hp = g_EnemyTypes[e.typeId].hp; // �G��HP��ݒ�
			break; // �ŏ��̖����ȓG����������I��
		}
	}
}

bool Enemy_IsEnable(int index)
{
	return g_Enemies[index].isEnabled;
}

Circle Enemy_GetCollision(int index)
{
	Enemy& e = g_Enemies[index]; // �G�̏����擾
	int id = g_Enemies[index].typeId; // �G�̃^�C�vID���擾
	//float cx = g_Enemies[index].position.x + g_EnemyTypes[id].collision.center.x; // �G�̒��SX���W
	//float cy = g_Enemies[index].position.y + g_EnemyTypes[id].collision.center.y; // �G�̒��SY���W
	float cx = e.position.x + e.collision.center.x; // �G�̒��SX���W
	float cy = e.position.y + e.collision.center.y; // �G�̒��SX���W

	return { { cx, cy }, e.collision.radius }; // �G�̏Փ˔���p�̉~��Ԃ�

}

void Enemy_Destroy(int index)
{
	g_Enemies[index].isEnabled = false; // �G�𖳌���
}

void Enemy_Damege(int index)
{
	g_Enemies[index].hp--;

	if (g_Enemies[index].hp <= 0) {
		Enemy_Destroy(index); // HP��0�ȉ��ɂȂ�����G��j��
	}
}





