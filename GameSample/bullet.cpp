/*==============================================================================

   プレイヤー [player.cpp]
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
	XMFLOAT2 position{}; // 弾の位置
	XMFLOAT2 velocity{}; // 弾の速度
	bool isEnabled; // 弾が有効かどうか
	double life_time; // 弾のライフタイム
};

// BULLET MAX
static constexpr unsigned int BULLET_MAX = 1024; // 弾の最大数
static Bullet g_Bullets[BULLET_MAX]{}; // 弾の配列
static int g_BulletTexId = -1;

void Bullet_Initialize()
{
	// 弾の初期化処理をここに記述
	// 例: 弾の位置、速度、ライフなどの初期値設定
	// g_BulletPosition = position;
	// g_BulletVelocity = { 0.0f, 0.0f }; // 初期速度はゼロ
	// g_BulletTexId = Texture_Load(L"bullet.png"); // 弾のテクスチャを読み込む
	for (Bullet& b : g_Bullets) {
		b.isEnabled = false; // 初期化時は全て無効
	}
	g_BulletTexId = Texture_Load(L"bullet.png"); // 弾のテクスチャを読み込む

}

void Bullet_Finalize()
{
	// 弾の終了処理をここに記述
	// 例: メモリの解放、リソースのクリーンアップなど
	// Texture_Release(g_BulletTexId); // 弾のテクスチャを解放
}

void Bullet_Update(double elapsed_time)
{
	// 弾の更新処理をここに記述
	// 例: 弾の位置、速度、ライフの更新など
	// XMVECTOR position = XMLoadFloat2(&g_BulletPosition);
	// XMVECTOR velocity = XMLoadFloat2(&g_BulletVelocity);
	// position += velocity * static_cast<float>(elapsed_time);
	// XMStoreFloat2(&g_BulletPosition, position);

	for (Bullet& b : g_Bullets) {
		if (!b.isEnabled) continue; // 弾が無効な場合はスキップ
		// 弾の位置を更新
		XMVECTOR position = XMLoadFloat2(&b.position);
		XMVECTOR velocity = XMLoadFloat2(&b.velocity);

		position += velocity * elapsed_time;

		// 弾の位置を保存
		XMStoreFloat2(&b.position, position);
		XMStoreFloat2(&b.velocity, velocity);
		// ライフタイムを更新
		b.life_time += elapsed_time; // ライフタイムを減少

		if (b.life_time > 5.0f) {
			b.isEnabled = false; // ライフタイムが0以下になったら弾を無効化
		}

		// 画面外に出たら弾を無効化
		if (b.position.y < 0.0f || b.position.y > Direct3D_GetBackBufferHeight() ||
			b.position.x < 0.0f || b.position.x > Direct3D_GetBackBufferWidth()) {
			b.isEnabled = false; 
		}
	}

}

void Bullet_Draw()
{
	// 弾の描画処理をここに記述
	// 例: 弾の位置にテクスチャを描画する
	// Sprite_Draw(g_BulletTexId, g_BulletPosition.x, g_BulletPosition.y, 32.0f, 32.0f);
	for (const Bullet& b : g_Bullets) {
		if (!b.isEnabled) continue; // 弾が無効な場合はスキップ
		Sprite_Draw(g_BulletTexId, b.position.x, b.position.y, 32.0f, 32.0f);
	}
}


void Bullet_Create(const DirectX::XMFLOAT2& position)  
{  
    for (Bullet& b : g_Bullets) {  
        if (!b.isEnabled) { // 弾が無効な場合はスキップしない  
            // 空き領域を見つけたら、その弾を有効化して初期化  
            b.isEnabled = true; // 弾を有効化  
            b.life_time = 0.0; // ライフタイムを設定  
            b.position = position; // 弾の初期位置を設定  
            b.velocity = DirectX::XMFLOAT2(200.0f, 0.0f); // 上方向に発射する速度を設定  
            break;  
        }  
    }  
}
