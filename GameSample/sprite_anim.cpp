/*==============================================================================

   Sprite animation[sprite_anim.cpp]
														 Author : LCH
														 Date   : 2025/06/17
--------------------------------------------------------------------------------

==============================================================================*/
#include "sprite_anim.h"
#include "sprite.h"
#include "texture.h"
#include <DirectXMath.h>
using namespace DirectX;

struct AnimPatternData
{
	int m_TextureId{ -1 }; //Currently playing pattern number
	int m_PatternMax = 0; //texture ID

	int m_HPatternMax = 0; //â°ÇÃPatternç≈ëÂêî
	XMUINT2 m_StartPosition  { 0,0 }; //Animation start coordinates
	XMUINT2 m_PatternSize{0,0}; //pattern size
	double m_seconds_per_pattern = 0.1;
	bool m_IsLooped{true};//LoopÇ∑ÇÈÇ©
};
struct AnimPlayData
{
	int m_PatternId = -1;
	int m_PatternNum = 0; //patternNumbers
	double m_AccumulatedTime = 0.0; //Cumulative time
};

static constexpr int ANIM_PATTERN_MAX = 128;
static AnimPatternData g_AnimPattern[ANIM_PATTERN_MAX];
static constexpr int ANIM_PLAY_MAX = 256;   //if not enough use 512
static AnimPlayData g_AnimPlay[ANIM_PLAY_MAX];

void SpriteAnim_Initialize()
{
	for (AnimPatternData& data : g_AnimPattern) {
		data.m_TextureId = -1;
	}

	for (AnimPlayData& data : g_AnimPlay) {
		data.m_PatternId = -1;
	}
}
	void SpriteAnim_Finalize()
	{
	}
	void SpriteAnim_Update(double elapsed_time)
	{
		for (int i = 0; i < ANIM_PLAY_MAX; i++) {

			if (g_AnimPlay[i].m_PatternId < 0) continue;

			AnimPatternData* pAnimPatternData = &g_AnimPattern[g_AnimPlay[i].m_PatternId];

			if (g_AnimPlay[i].m_AccumulatedTime >= pAnimPatternData->m_seconds_per_pattern)
			{
				g_AnimPlay[i].m_PatternNum++;

				if (g_AnimPlay[i].m_PatternNum >= pAnimPatternData->m_PatternMax) 
				{
					if (pAnimPatternData->m_IsLooped) 
					{
						g_AnimPlay[i].m_PatternNum = 0;
					}
					else 
{
						g_AnimPlay[i].m_PatternNum = pAnimPatternData->m_PatternMax - 1;
					}
				}

				g_AnimPlay[i].m_AccumulatedTime -= pAnimPatternData->m_seconds_per_pattern;
			}
			g_AnimPlay[i].m_AccumulatedTime += elapsed_time;
		}
	}

	void SpriteAnim_Draw(int playid, float dx, float dy, float dw, float dh) //add numbers if you want to chnage polygn size
	{
		int anim_pattern_id = g_AnimPlay[playid].m_PatternId;
		AnimPatternData* pAnimPatternData = &g_AnimPattern[anim_pattern_id];

		//caculator 

		Sprite_Draw(pAnimPatternData->m_TextureId,
			dx, dy, dw, dh,
			pAnimPatternData->m_StartPosition.x
			+ pAnimPatternData->m_PatternSize.x
			* (g_AnimPlay[playid].m_PatternNum % pAnimPatternData->m_HPatternMax),
			pAnimPatternData->m_StartPosition.y
			+pAnimPatternData->m_PatternSize.y
			* (g_AnimPlay[playid].m_PatternNum / pAnimPatternData->m_HPatternMax),
			pAnimPatternData->m_PatternSize.x,
			pAnimPatternData->m_PatternSize.y
		);
	}

	int SpriteAnim_RegisterPattern(int texid, int pattern_max,int h_pattern_max, double seconds_per_pattern, const DirectX::XMUINT2& pattern_size, const DirectX::XMUINT2& start_position, bool is_looped)
	{
		for (int i = 0; i < ANIM_PATTERN_MAX; i++) {
			// ãÛÇ¢ÇƒÇÈèÍèäÇíTÇ∑
			if (g_AnimPattern[i].m_TextureId >= 0) continue;

			g_AnimPattern[i].m_TextureId = texid;
			g_AnimPattern[i].m_PatternMax = pattern_max;
			g_AnimPattern[i].m_HPatternMax = h_pattern_max;
			g_AnimPattern[i].m_seconds_per_pattern =seconds_per_pattern;
			g_AnimPattern[i].m_PatternSize = pattern_size;
			g_AnimPattern[i].m_StartPosition = start_position;
			g_AnimPattern[i].m_IsLooped = is_looped;

			return i;
		}
		// ãÛÇ´Ç™Ç»Ç©Ç¡ÇΩèÍçá
		return -1;
	}

	int SpriteAnim_CreatePlayer(int anim_pattern_id)
	{
		for (int i = 0; i < ANIM_PLAY_MAX; i++) {
			if (g_AnimPlay[i].m_PatternId >= 0) continue;

			g_AnimPlay[i].m_PatternId = anim_pattern_id;
			g_AnimPlay[i].m_AccumulatedTime = 0.0;
			g_AnimPlay[i].m_PatternNum = 0;

			return i;
		}
		return -1;
	}


