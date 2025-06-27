
#include "game.h"
#include "player.h"

void Game_Initialize()
{
	Player_Initialize({ 64.0f, 450 - 32.0f }); // プレイヤーの初期位置を設定
	// 他の初期化処理があればここに追加	Player_Initialize();
}

void Game_Finalize()
{
}

void Game_Update(double elapsed_time)
{
	Player_Update(elapsed_time); // プレイヤーの更新処理を呼び出す
	// 他の更新処理があればここに追加
	// 例: 敵の更新、スコアの更新など
}

void Game_Draw()
{
	Player_Draw();
}
