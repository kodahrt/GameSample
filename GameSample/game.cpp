
#include "game.h"
#include "player.h"
#include "bullet.h"

void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f }); // プレイヤーの初期位置を設定
	// 他の初期化処理があればここに追加	Player_Initialize();
	Bullet_Initialize();
}

void Game_Finalize()
{
	Player_Finalize(); // プレイヤーの終了処理を呼び出す
	Bullet_Finalize(); // 弾の終了処理を呼び出す
	// 他の終了処理があればここに追加
	// 例: 敵の終了、スコアの保存など
}

void Game_Update(double elapsed_time)
{
	Player_Update(elapsed_time); // プレイヤーの更新処理を呼び出す
	// 他の更新処理があればここに追加
	// 例: 敵の更新、スコアの更新など
	Bullet_Update(elapsed_time); // 弾の更新処理を呼び出す
}

void Game_Draw()
{
	
	// ゲームの描画処理をここに記述
	Bullet_Draw(); 
	Player_Draw();
}
