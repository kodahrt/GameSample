/*========================================================================================


    敵の制御 (Enemy CPP)												LCH
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
	int texId; // 敵のテクスチャID
	int tx, ty, tw, th; // テクスチャのUV座標とサイズ
	XMFLOAT2 velocity; // 敵の速度
	Circle collision; // 敵の衝突判定用の円

	// status
	int hp; // 敵の最大HP
};

struct Enemy
{
	int typeId; // 敵のタイプID
	XMFLOAT2 position; // 敵の位置
	XMFLOAT2 velocity; // 敵の速度
	float offsetY; // 敵のYオフセット（アニメーション用など）
	double lifeTime; // 敵のライフタイム
	bool isEnabled; // 敵が有効かどうか

	Circle collision; // 敵の衝突判定用の円

	int hp; // 敵のHP
};


static Enemy g_Enemies[ENEMY_MAX]{}; // 敵の配列
static int g_EnemyTexId = -1; // 敵のテクスチャID
static constexpr float ENEMY_WIDTH = 32.0f; // 敵の幅
static constexpr float ENEMY_HEIGHT = 32.0f; // 敵の高さ
static EnemyType g_EnemyTypes[]{
	{ -1, 32, 32, 10 }, // 敵のタイプ1
	{ -1, 32, 32, 2 } // 敵のタイプ2
	// 他の敵のタイプを追加する場合はここに記述
};

void Enemy_Initialize()  
{  
   for (Enemy& e : g_Enemies) {  
       e.isEnabled = false; // 初期化時は全て無効  
   }  
   //g_EnemyTypes[0].texId = Texture_Load(L"enemy.png"); // 弾のテクスチャを読み込む  
   //g_EnemyTypes[1].texId = Texture_Load(L"enemy.png"); // 弾のテクスチャを読み込む  
   g_EnemyTexId = Texture_Load(L"enemy.png"); // 敵のテクスチャを読み込む
}

void Enemy_Finalize()
{

}

void Enemy_Update(double elapsed_time)
{
	for (Enemy& e : g_Enemies) {
		if (!e.isEnabled) continue; // 弾が無効な場合はスキップ

		switch (e.typeId)
		{
		case ENEMY_TYPE_2SHOT:
			// 2WAY弾の処理
			e.position.x += e.velocity.x * elapsed_time;
			e.position.y = e.offsetY * sinf(e.lifeTime) * 100.0f; // Y軸のオフセットをサイン波で更新
			break;
		case ENEMY_TYPE_NORMAL:
			XMVECTOR position = XMLoadFloat2(&e.position);
			XMVECTOR velocity = XMLoadFloat2(&e.velocity);
			// 弾の位置を保存
			XMStoreFloat2(&e.position, position);
			XMStoreFloat2(&e.velocity, velocity);
			// 通常弾の処理
			position += velocity * static_cast<float>(elapsed_time); // 弾の位置を更新
			break;
		}



		e.lifeTime += elapsed_time; // ライフタイムを更新
		
		if (e.position.x < 0.0f ) {
			e.isEnabled = false; // 画面外に出たら無効化
		}

	}
}

void Enemy_Draw()
{
	for (Enemy& e : g_Enemies) {
		if (!e.isEnabled) continue; // 弾が無効な場合はスキップ
		Sprite_Draw(g_EnemyTexId, e.position.x, e.position.y, ENEMY_WIDTH, ENEMY_HEIGHT);
	};
}

void Enemy_Create(EnemyTypeID id, const DirectX::XMFLOAT2& position)
{
	for (Enemy& e : g_Enemies) {
		if (!e.isEnabled) {
			e.position = position; // 敵の位置を設定
			e.typeId = id; // 敵のタイプを設定
			e.lifeTime = 0.0; // 敵のライフタイムを初期化
			e.offsetY = position.y; // Yオフセットを初期化
			e.velocity = { -200.0f, 0.0f }; // 左方向に移動
			e.isEnabled = true; // 敵を有効化
			e.hp = g_EnemyTypes[e.typeId].hp; // 敵のHPを設定
			break; // 最初の無効な敵を見つけたら終了
		}
	}
}

bool Enemy_IsEnable(int index)
{
	return g_Enemies[index].isEnabled;
}

Circle Enemy_GetCollision(int index)
{
	Enemy& e = g_Enemies[index]; // 敵の情報を取得
	int id = g_Enemies[index].typeId; // 敵のタイプIDを取得
	//float cx = g_Enemies[index].position.x + g_EnemyTypes[id].collision.center.x; // 敵の中心X座標
	//float cy = g_Enemies[index].position.y + g_EnemyTypes[id].collision.center.y; // 敵の中心Y座標
	float cx = e.position.x + e.collision.center.x; // 敵の中心X座標
	float cy = e.position.y + e.collision.center.y; // 敵の中心X座標

	return { { cx, cy }, e.collision.radius }; // 敵の衝突判定用の円を返す

}

void Enemy_Destroy(int index)
{
	g_Enemies[index].isEnabled = false; // 敵を無効化
}

void Enemy_Damege(int index)
{
	g_Enemies[index].hp--;

	if (g_Enemies[index].hp <= 0) {
		Enemy_Destroy(index); // HPが0以下になったら敵を破壊
	}
}





