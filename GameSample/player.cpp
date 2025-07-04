/*==============================================================================

   プレイヤー [player.cpp]
														 Author : LCH
														 Date   : 2025/06/27
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "sprite.h"
#include "texture.h"
#include "key_logger.h"	
#include "bullet.h"
#include "direct3d.h"
#include "debug_ostream.h"
#include "collision.h"

static XMFLOAT2 g_PlayerPosition{};
static XMFLOAT2 g_PlayerVelocity{}; // プレイヤーの速度
static int g_PlayerTexId = -1; // プレイヤーのテクスチャID;
static constexpr Circle g_PlayerCollision = { {32.0f, 32.0f}, 32.0f }; // プレイヤーの衝突判定用の円
static bool g_PlayerEnable = true; // プレイヤーが有効かどうか



void Player_Initialize(const XMFLOAT2& position)
{
	// プレイヤーの初期化処理をここに記述
	// 例: プレイヤーの位置、スコア、ライフなどの初期値設定
	g_PlayerPosition = position;
	g_PlayerVelocity = { 0.0f, 0.0f }; // 初期速度はゼロ
	// プレイヤーのテクスチャを読み込む
	g_PlayerTexId = Texture_Load(L"kokosozai.png");
	g_PlayerEnable = true; // プレイヤーを有効化
}

void Player_Finalize()
{

}

// プレイヤーの更新処理
void Player_Update(double elapsed_time)
{
	if (!g_PlayerEnable) return; // プレイヤーが無効な場合は描画しない

	XMVECTOR position = XMLoadFloat2(&g_PlayerPosition);
	XMVECTOR velocity = XMLoadFloat2(&g_PlayerVelocity);
	
	XMVECTOR direction{};
	// キーボード入力を取得
	if (KeyLogger_IsPressed(KK_W)) {
		direction += {0.0f, -1.0f}; // 上方向
	}
	if (KeyLogger_IsPressed(KK_A)) {
		direction += {-1.0f, 0.0f}; // 左方向
	}
	if (KeyLogger_IsPressed(KK_S)) {
		direction += {0.0f, 1.0f}; // 下方向
	}
	if (KeyLogger_IsPressed(KK_D)) {
		direction += {1.0f, 0.0f}; // 右方向
	}

	direction = XMVector2Normalize(direction); // 正規化して方向ベクトルを取得

	velocity += direction * 2.0f; // 速度を更新

	position += velocity;

	velocity *= 0.9f; // 摩擦を模擬するために速度を減衰

	// 画面の端で反転する処理
	//if (XMVectorGetX(position) < 0.0f) {
	//	position = XMVectorSet(0.0f, XMVectorGetY(position), 0.0f, 0.0f); // 左端で反転
	//	velocity = XMVectorSet(-XMVectorGetX(velocity), XMVectorGetY(velocity), 0.0f, 0.0f);
	//}
	//else if (XMVectorGetX(position) > Direct3D_GetBackBufferWidth() - 32.0f) {
	//	position = XMVectorSet(Direct3D_GetBackBufferWidth() - 32.0f, XMVectorGetY(position), 0.0f, 0.0f); // 右端で反転
	//	velocity = XMVectorSet(-XMVectorGetX(velocity), XMVectorGetY(velocity), 0.0f, 0.0f);
	//}

// ======================================================================================================================

	//velocity += direction * 6000000.0f / 2500.0f * elapsed_time; // 速度を更新

	//position += velocity * elapsed_time;

	//velocity += -velocity * 4.0f * elapsed_time; // 摩擦を模擬するために速度を減衰
	
// ======================================================================================================================
	// 画面の端で反転する処理 
	XMStoreFloat2(&g_PlayerPosition, position);
	XMStoreFloat2(&g_PlayerVelocity, velocity);

	if (KeyLogger_IsTrigger(KK_SPACE)) {
		Bullet_Create({ g_PlayerPosition.x + 100.0f , g_PlayerPosition.y + 50.0f });
	}

	// 画面外に出たら位置をリセット
	if (g_PlayerPosition.x < 0.0f) {
		g_PlayerPosition.x = 0.0f; // 左端で位置をリセット
	}
	else if (g_PlayerPosition.x > Direct3D_GetBackBufferWidth() - 32.0f) {
		g_PlayerPosition.x = Direct3D_GetBackBufferWidth() - 32.0f; // 右端で位置をリセット
	}
}

void Player_Draw()
{
	if (!g_PlayerEnable) return; // プレイヤーが無効な場合は描画しない

	// プレイヤーの描画処理をここに記述
	Sprite_Draw(g_PlayerTexId,
		g_PlayerPosition.x, g_PlayerPosition.y,
		128.0f, 128.0f,
		0.0f, 0.0f,
		32.0f, 32.0f);
}

bool Player_IsEnable()
{
	return g_PlayerEnable;
}

Circle Player_GetCollision()
{
	float cx = g_PlayerPosition.x + g_PlayerCollision.center.x;
	float cy = g_PlayerPosition.y + g_PlayerCollision.center.y;
	
	return { {cx, cy}, g_PlayerCollision.radius }; // プレイヤーの衝突判定用の円を返す
}

void Player_Destroy()
{
	g_PlayerEnable = false; // プレイヤーを無効化
}
