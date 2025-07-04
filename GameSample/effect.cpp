// ==========================================================================================================

// Effect.cpp

																			//	LEE CHEE HOW

// /*========================================================================================================
#include "effect.h"
#include <DirectXMath.h>
#include "direct3d.h"
#include "sprite_anim.h"
#include "texture.h"
using namespace DirectX;
// Effectの構造体
struct Effect
{
	XMFLOAT2 position{}; // 弾の位置
//	XMFLOAT2 velocity{}; // 弾の速度
	int sprite_anim_id; // スプライトアニメーションID
	bool isEnabled; // 弾が有効かどうか
//	double life_time; // 弾のライフタイム
//	Circle collision; // 弾の衝突判定用の円
};

static constexpr int EFFECT_MAX = 256; // 弾の最大数
static Effect g_Effects[EFFECT_MAX]{}; // 弾の配列
static int g_EffectTexId = -1; // 弾のテクスチャID
static int g_AnimPatternId = -1; // スプライトアニメーションのパターンID

void Effect_Initialize()
{
	for (Effect& e : g_Effects) {
		e.isEnabled = false; // 初期化時は全て無効
	}

	g_EffectTexId = Texture_Load(L"Explosion.png"); // 弾のテクスチャを読み込む
	g_AnimPatternId = SpriteAnim_RegisterPattern(
		g_EffectTexId, 16, 4, // パターンの横と縦の数
		0.05, // 1フレームあたりの秒数
		{ 256, 256 }, // パターンのサイズ
		{ 0, 0 }, // 開始位置
		false // ループするかどうか
	);
}

void Effect_Finalize()
{
}

void Effect_Update(double elapsed_time)
{
	for (Effect& e : g_Effects) {
		if (!e.isEnabled) continue;

		if (SpriteAnim_IsStopped(e.sprite_anim_id)) {
			SpriteAnim_DestroyPlayer(e.sprite_anim_id); // スプライトアニメーションを破棄
			e.isEnabled = false; // スプライトアニメーションが停止したら弾を無効化
		}
	}
}

void Effect_Draw()
{
	for (const Effect& e : g_Effects) {
		if (!e.isEnabled) continue; // 弾が無効な場合はスキップ
		SpriteAnim_Draw(e.sprite_anim_id, e.position.x, e.position.y, 64.0f, 64.0f);
	}
}

void Effect_Create(const DirectX::XMFLOAT2& position, int typeId)
{
	for (Effect& e : g_Effects) {
		if (e.isEnabled) continue;  // 弾が無効な場合はスキップしない  
			// 空き領域を見つけたら、その弾を有効化して初期化  
		e.isEnabled = true; // 弾を有効化
		e.position = position; // 弾の初期位置を設定
		e.sprite_anim_id = SpriteAnim_CreatePlayer(typeId); // スプライトアニメーションを作成
		break;
	}
}
