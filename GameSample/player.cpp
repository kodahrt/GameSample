/*==============================================================================

   プレイヤー [player.h]
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

static XMFLOAT2 g_PlayerPosition{};
static XMFLOAT2 g_PlayerVelocity{}; // プレイヤーの速度
static int g_PlayerTexId = -1; // プレイヤーのテクスチャID;

void Player_Initialize(const XMFLOAT2& position)
{
	// プレイヤーの初期化処理をここに記述
	// 例: プレイヤーの位置、スコア、ライフなどの初期値設定
	g_PlayerPosition = position;
	g_PlayerVelocity = { 0.0f, 0.0f }; // 初期速度はゼロ
	// プレイヤーのテクスチャを読み込む
	g_PlayerTexId = Texture_Load(L"kokosozai.png");
}

void Player_Finalize()
{

}

// プレイヤーの更新処理
void Player_Update(double elapsed_time)
{
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

	velocity += direction * 100.0f * elapsed_time; // 速度を更新

	position += velocity;

	velocity *= 0.95f; // 摩擦を模擬するために速度を減衰
	// 画面の端で反転する処理 
	XMStoreFloat2(&g_PlayerPosition, position);
	XMStoreFloat2(&g_PlayerVelocity, position);


}

void Player_Draw()
{
	Sprite_Draw(g_PlayerTexId,
		g_PlayerPosition.x, g_PlayerPosition.y,
		128.0f, 128.0f,
		0.0f, 0.0f,
		32.0f, 32.0f);
}