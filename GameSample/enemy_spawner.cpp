/*========================================================================================


    敵の発生制御 (EnemySpawner CPP)							LCH
                                                            DATE:02/07/2005

-------------------------------------------------------------------------------------------=
=========================================================================================*/
#include "enemy_spawner.h"
#include "enemy.h"
#include <DirectXMath.h>
using namespace DirectX;


struct EnemySpawn
{
	XMFLOAT2 position; // 敵の生成位置
	EnemyTypeID typeId; // 敵のタイプID
	double spawnTime; // 敵の生成時刻
	double spawnRate; // 敵の生成間隔
	int count;
	int spawnCount; // 生成する敵の数
	double time;
	bool isEnded; // 敵の生成が終了したかどうか
};

static constexpr unsigned int ENEMY_SPAWN_MAX = 100; // 敵の生成の最大数
static EnemySpawn g_EnemySpawns[ENEMY_SPAWN_MAX] {}; // 敵の生成の配列
static int g_SpawnerCount = 0; // 現在の生成数
static double g_Time = 0.0; // 最後に実行した時刻

void EnemySpawner_Initialize()
{
	g_SpawnerCount = 0; // 生成数を初期化
	g_Time = 0.0; // 時刻を初期化
}

void EnemySpawner_Finalize()
{

}

void EnemySpawner_Update(double elapsed_time)
{
	g_Time += elapsed_time; // 時刻を更新
	for (int i = 0; i < g_SpawnerCount; i++) {
		if (g_EnemySpawns[i].isEnded) continue; // 生成が終了した場合はスキップ
		if (g_EnemySpawns[i].spawnTime > g_Time) break;

		if (g_EnemySpawns[i].count == 0) {
			g_EnemySpawns[i].spawnTime = g_Time - g_EnemySpawns[i].spawnRate - 0.00001; // 初回の生成時刻を設定
		}

		// 生成時刻が現在の時刻を過ぎている場合、敵を生成
		if (g_Time - g_EnemySpawns[i].spawnTime >= g_EnemySpawns[i].spawnRate) {
			Enemy_Create(g_EnemySpawns[i].typeId, g_EnemySpawns[i].position);
			g_EnemySpawns[i].count++;
			if (g_EnemySpawns[i].count >= g_EnemySpawns[i].spawnCount) {
				g_EnemySpawns[i].isEnded = true; // 生成が終了
			}
			g_EnemySpawns[i].spawnTime = g_Time; // 次の生成時刻を更新
		}
	}
}

void EnemySpawner_Create(const DirectX::XMFLOAT2& position, EnemyTypeID id, double spawn_time, double spawn_rate, int spawn_count)
{
	if (g_SpawnerCount >= ENEMY_SPAWN_MAX) {
		return; // 生成数が最大に達している場合は何もしない
	}
	EnemySpawn* pEs = &g_EnemySpawns[g_SpawnerCount];
	pEs->position = position; // 敵の生成位置を設定
	pEs->typeId = id; // 敵のタイプIDを設定
	pEs->spawnTime = spawn_time; // 敵の生成時刻を設定
	pEs->spawnRate = spawn_rate; // 敵の生成間隔を設定
	pEs->count = 0; // 生成数を初期化
	pEs->spawnCount = spawn_count; // 生成する敵の数を設定
	pEs->isEnded = false; // 生成が終了していない状態に設定
	pEs->time = 0.0; // 時刻を初期化
	g_SpawnerCount++; // 生成数を増加
}
