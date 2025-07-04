
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy_spawner.h"
#include "effect.h"

static double g_Time = 0.0; // 最後に実行した時刻
static double g_CreateTime = 0.0;

void hitJudgmentBulletVSEnemy(); // 弾と敵の衝突判定を行う関数の宣言
void hitJudgmentPlayertVSEnemy(); // プレイヤーと敵の衝突判定を行う関数の宣言

void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f }); // プレイヤーの初期位置を設定
	// 他の初期化処理があればここに追加	Player_Initialize();
	Bullet_Initialize(); // 弾の初期化処理を呼び出す
	Enemy_Initialize(); // 敵の初期化処理を呼び出す
	EnemySpawner_Initialize(); // 敵の発生制御の初期化処理を呼び出す

	// 敵の生成例
	EnemySpawner_Create({ 1600.0f, 450 - 64 }, ENEMY_TYPE_2SHOT, 3.0f ,	0.5, 5); // 敵の生成を設定
}

void Game_Finalize()
{
	Player_Finalize(); // プレイヤーの終了処理を呼び出す
	Bullet_Finalize(); // 弾の終了処理を呼び出す
	// 他の終了処理があればここに追加
	// 例: 敵の終了、スコアの保存など
	Enemy_Finalize(); // 敵の終了処理を呼び出す
	EnemySpawner_Finalize(); // 敵の発生制御の終了処理を呼び出す
}

void Game_Update(double elapsed_time)
{
	EnemySpawner_Update(elapsed_time); // 敵の発生制御の更新処理を呼び出す
	Player_Update(elapsed_time); // プレイヤーの更新処理を呼び出す
	// 他の更新処理があればここに追加
	// 例: 敵の更新、スコアの更新など
	Bullet_Update(elapsed_time); // 弾の更新処理を呼び出す
	Enemy_Update(elapsed_time); // 敵の更新処理を呼び出す

	hitJudgmentBulletVSEnemy(); // 弾と敵の衝突判定を行う
	hitJudgmentPlayertVSEnemy(); // プレイヤーと敵の衝突判定を行う

	Effect_Update(elapsed_time); // エフェクトの更新処理を呼び出す
}

void Game_Draw()
{
	// ゲームの描画処理をここに記述
	Enemy_Draw();
	Bullet_Draw(); 
	Player_Draw();
	Effect_Draw(); // エフェクトの描画処理を呼び出す
}

void hitJudgmentBulletVSEnemy()
{
	for (int bi = 0; bi < BULLET_MAX; bi++) {   
		if (!Bullet_IsEnable(bi)) continue; // 弾が無効な場合はスキップ
		Circle bulletCollision = Bullet_GetCollision(bi); // 弾の衝突判定用の円を取得
		for (int ei = 0; ei < ENEMY_MAX; ei++) {
			if (!Enemy_IsEnable(ei)) continue; // 敵が無効な場合はスキップ
			Circle enemyCollision = Enemy_GetCollision(ei); // 敵の衝突判定用の円を取得
			if (Collision_IsOverlapCircle(bulletCollision, enemyCollision)) {
				// 弾と敵が衝突した場合の処理
				Bullet_Destroy(bi); // 弾を破                                                                                                              壊
				Enemy_Damege(ei); // 敵にダメージを与える
			}
		}
	}
}

void hitJudgmentPlayertVSEnemy()
{		
	if (!Player_IsEnable()) return; // プレイヤーが無効な場合はスキップ
	for (int ei = 0; ei < ENEMY_MAX; ei++) {
		if (!Enemy_IsEnable(ei)) continue; // 敵が無効な場合はスキップ
		Circle enemyCollision = Enemy_GetCollision(ei); // 敵の衝突判定用の円を取得
		if (Collision_IsOverlapCircle(Player_GetCollision(), enemyCollision)) {
			// プレイヤーと敵が衝突した場合の処理
			Player_Destroy(); // プレイヤーを破壊
			Enemy_Destroy(ei); // 敵を破壊
		}
	}
    
}
