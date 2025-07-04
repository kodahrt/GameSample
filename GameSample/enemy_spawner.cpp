/*========================================================================================


    �G�̔������� (EnemySpawner CPP)							LCH
                                                            DATE:02/07/2005

-------------------------------------------------------------------------------------------=
=========================================================================================*/
#include "enemy_spawner.h"
#include "enemy.h"
#include <DirectXMath.h>
using namespace DirectX;


struct EnemySpawn
{
	XMFLOAT2 position; // �G�̐����ʒu
	EnemyTypeID typeId; // �G�̃^�C�vID
	double spawnTime; // �G�̐�������
	double spawnRate; // �G�̐����Ԋu
	int count;
	int spawnCount; // ��������G�̐�
	double time;
	bool isEnded; // �G�̐������I���������ǂ���
};

static constexpr unsigned int ENEMY_SPAWN_MAX = 100; // �G�̐����̍ő吔
static EnemySpawn g_EnemySpawns[ENEMY_SPAWN_MAX] {}; // �G�̐����̔z��
static int g_SpawnerCount = 0; // ���݂̐�����
static double g_Time = 0.0; // �Ō�Ɏ��s��������

void EnemySpawner_Initialize()
{
	g_SpawnerCount = 0; // ��������������
	g_Time = 0.0; // ������������
}

void EnemySpawner_Finalize()
{

}

void EnemySpawner_Update(double elapsed_time)
{
	g_Time += elapsed_time; // �������X�V
	for (int i = 0; i < g_SpawnerCount; i++) {
		if (g_EnemySpawns[i].isEnded) continue; // �������I�������ꍇ�̓X�L�b�v
		if (g_EnemySpawns[i].spawnTime > g_Time) break;

		if (g_EnemySpawns[i].count == 0) {
			g_EnemySpawns[i].spawnTime = g_Time - g_EnemySpawns[i].spawnRate - 0.00001; // ����̐���������ݒ�
		}

		// �������������݂̎������߂��Ă���ꍇ�A�G�𐶐�
		if (g_Time - g_EnemySpawns[i].spawnTime >= g_EnemySpawns[i].spawnRate) {
			Enemy_Create(g_EnemySpawns[i].typeId, g_EnemySpawns[i].position);
			g_EnemySpawns[i].count++;
			if (g_EnemySpawns[i].count >= g_EnemySpawns[i].spawnCount) {
				g_EnemySpawns[i].isEnded = true; // �������I��
			}
			g_EnemySpawns[i].spawnTime = g_Time; // ���̐����������X�V
		}
	}
}

void EnemySpawner_Create(const DirectX::XMFLOAT2& position, EnemyTypeID id, double spawn_time, double spawn_rate, int spawn_count)
{
	if (g_SpawnerCount >= ENEMY_SPAWN_MAX) {
		return; // ���������ő�ɒB���Ă���ꍇ�͉������Ȃ�
	}
	EnemySpawn* pEs = &g_EnemySpawns[g_SpawnerCount];
	pEs->position = position; // �G�̐����ʒu��ݒ�
	pEs->typeId = id; // �G�̃^�C�vID��ݒ�
	pEs->spawnTime = spawn_time; // �G�̐���������ݒ�
	pEs->spawnRate = spawn_rate; // �G�̐����Ԋu��ݒ�
	pEs->count = 0; // ��������������
	pEs->spawnCount = spawn_count; // ��������G�̐���ݒ�
	pEs->isEnded = false; // �������I�����Ă��Ȃ���Ԃɐݒ�
	pEs->time = 0.0; // ������������
	g_SpawnerCount++; // �������𑝉�
}
